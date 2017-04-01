#include "Connector.h"


Connector::Connector(nlohmann::json &json, Connector::Listener listener): service() {
	this->listener = listener;
	if (json.find("name") != json.end()) {
		std::string name = *json.find("name");
		port = std::unique_ptr<boost::asio::serial_port>(new boost::asio::serial_port(service, name.c_str()));
	} else {
		throw std::invalid_argument("Missing 'name' in 'connector' object");
	}
	if (json.find("baudrate") != json.end()) {
		port->set_option(boost::asio::serial_port::baud_rate(static_cast<uint32_t>(*json.find("baudrate"))));
	} else {
		throw std::invalid_argument("Missing 'baudrate' in 'connector' object");
	}
	port->set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

	threads.create_thread(boost::bind(&boost::asio::io_service::run, &service));
	threads.create_thread([&, this](){
		boost::system::error_code ec;
		uint8_t *buffer = new uint8_t[128];
		while (this->listener && !boost::this_thread::interruption_requested()) {
			try {
				if (auto size = port->read_some(boost::asio::buffer(buffer, 128), ec))
					for (int i = 0; i < size; i++)
						this->listener(buffer[i]);
				usleep(5000);
			} catch (...) { port->cancel(); }
		}
		delete buffer;
	});
}

Connector::~Connector() {
	if (port)
		port->close();

	threads.interrupt_all();
	threads.join_all();
}

void Connector::write(std::vector<uint8_t> &message) {
	std::vector<uint8_t> vector(message.begin(), message.end());
	port->async_write_some(boost::asio::buffer(vector), [](auto ec, auto size) {});
}

