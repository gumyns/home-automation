#include "Application.h"
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
#include <config/Config.h>
#include <utils/Logger.h>
#include <hardware/HardwareManager.h>
#include <thread>
#include <openhab/BindingManager.h>
#include <openhab/AddressConverter.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

static constexpr const char * FRAME_PUBLISH_CHANNEL = "inproc://publishFrame";

/*! NOTE that ACK/ALIVE Frame is just trailing 0 - expressed as empty reply */
enum MessageType {
	BINDING = 0x01,
	IDENT = 0x02,
	JSON = 0x03,
	ERROR = 0xFF
};

class gumyns::sh::Application::Impl {

public:
	Impl() {}

	~Impl() {}

	zmq::message_t generateMessage(const void *src, size_t offset, size_t size) {
		zmq::message_t message (size + offset + 1);
		memset(message.data() + offset, 0, size + 1);
		memcpy (message.data() + offset, src, size);
		return message;
	}

	int run(gumyns::sh::config::Config::uPtr config) {
		// Instantiate ZeroMQ context
		zmq::context_t context;
		// Instantiate Binding manager
		BindingManager::uPtr bindings(new BindingManager());
		// Create connection to database
		DatabaseService::sPtr dbService = DatabaseService::create(config->database());
		// Instantiate plugins
		HardwareManager::uPtr hardware(new HardwareManager(*config.get(), dbService));
		// Attach FrameListener to internal signal
		hardware->setResponseListener([&](nlohmann::json json){
			// Connect internal socket and send json to publisher
			LogD << "<---" << json << std::endl;
			zmq::socket_t sender(context, ZMQ_PAIR);
			sender.connect(FRAME_PUBLISH_CHANNEL);
			auto buffer = json.dump();
			auto message = generateMessage(buffer.c_str(), 0, buffer.size() + 1);
			sender.send(message);
		});

		// Publisher thread - main purpose is to intercept internal messages from other threads, and to redirect them to publisher
		std::thread publisherThread([&](){
			zmq::socket_t publisher(context, ZMQ_PUB);
			publisher.bind(config->zeroPublisher());
			zmq::socket_t listener(context, ZMQ_PAIR);
			listener.bind(FRAME_PUBLISH_CHANNEL);

			while(true) {
				zmq::message_t request;
				listener.recv(&request);
				json_create_and_parse(json, request.data());
				if (auto address = AddressConverter::fromJson(json)) {
					nlohmann::json responseJson;
					responseJson["b"] = bindings->byAddress(address);
					if (json.find("r") != json.end()) {
						responseJson["r"] = json["r"];
						auto buffer = responseJson.dump();
						auto message = generateMessage(buffer.c_str(), 1, buffer.size());
						static_cast<uint8_t *>(message.data())[0] = static_cast<uint8_t>(MessageType::JSON);
						LogD << "<--" << buffer.size() + 1 << ":" << static_cast<char *>(message.data()) << std::endl;
						publisher.send(message);
					} else {
						auto buffer = responseJson.dump();
						auto message = generateMessage(buffer.c_str(), 1, buffer.size());
						static_cast<uint8_t *>(message.data())[0] = static_cast<uint8_t>(MessageType::IDENT);
						LogD << "<--" << buffer.size() + 1 << ":" << static_cast<char *>(message.data()) << std::endl;
						publisher.send(message);
					}
				}
			}
		});

		zmq::socket_t socket(context, ZMQ_REP);
		socket.bind(config->zeroEndpoint());

		// Main loop in app, just waits for incoming messages, parses them, moves to hardware manager and sends ACK (trailing 0) as response
		while (true) {
			zmq::message_t request;
			//  Wait for next request from client
			socket.recv (&request);
			// If there's only ACK/ALIVE
			uint8_t * buffer = static_cast<uint8_t *>(request.data());
			LogD << "-->" << toHexString(request.data(), request.size()) << std::endl;
			if (request.size() == 0) {
				zmq::message_t reply(0);
				LogD << "<-- ACK" << std::endl;
				socket.send (reply);
			} else { // If there's a request
				switch ((int)static_cast<uint8_t *>(request.data())[0]) {
					case MessageType::BINDING: {
						ZERO_BUFFER(requestBuffer, request.size() - 1)
						COPY_REQUEST(requestBuffer, request, 1)
						uint64_t addr = bindings->add((const uint8_t *)requestBuffer, request.size() - 1);
						nlohmann::json json = AddressConverter::toJson(addr);
						try {
							hardware->write(json);
						} catch (std::exception& e) {
							LogE << e.what();
						}
						zmq::message_t reply(0);
						socket.send(reply);
					} break;
					case MessageType::IDENT:
					case MessageType::JSON: {
						ZERO_BUFFER(requestBuffer, request.size() - 6)
						COPY_REQUEST(requestBuffer, request, 7)
						auto json = AddressConverter::toJson(AddressConverter::fromFrame(request.data()));
						nlohmann::json req = nlohmann::json::parse(requestBuffer);
						json["request"] = req;
						LogD << "-->" << json << std::endl;
						try {
							hardware->write(json);
						} catch (std::exception& e) {
							LogE << e.what();
							// TODO generate error frame maybe?
						}
						zmq::message_t reply(0);
						socket.send (reply);
					} break;
					default: {
						ZERO_BUFFER(requestBuffer, request.size() - 1)
						COPY_REQUEST(requestBuffer, request, 1)
						LogD << "Unknown request: " << requestBuffer << std::endl;
						zmq::message_t reply(1);
						static_cast<uint8_t *>(request.data())[0] = static_cast<uint8_t>(MessageType::ERROR);
						socket.send (reply);
					} break;
				}
			}

		}
		return 0;
	}
};
#pragma clang diagnostic pop

gumyns::sh::Application::Application() : pImpl(new Impl()) {}

gumyns::sh::Application::uPtr gumyns::sh::Application::create() { return uPtr(new Application()); }

int gumyns::sh::Application::run(int argc, char **argv) { return pImpl->run(gumyns::sh::config::Config::from(argc, argv));}

gumyns::sh::Application::~Application() {};

