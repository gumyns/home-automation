#include "HardwareManager.h"
#include "GatewayFactory.h"
#include "DeviceFactory.h"

class gumyns::sh::HardwareManager::Impl {
	GatewayFactory::uPtr hubFactory;
	DeviceFactory::uPtr deviceFactory;

	/*! Gateways are stored per 'real' socket or communication channel - so IDs */
	std::map<uint32_t, Gateway::sPtr> gateways;
	/*! Device parsers are stored per type of device - no real connection to physical objects, just parsers - so, Device type*/
	std::map<uint32_t, Device::sPtr> devices;
	/*! Multimap that contains as follows: gateway ID, hub address, device address -> device type */
	std::map<uint32_t, std::map<uint32_t, std::map<uint32_t, uint32_t>>> deviceMapping;

	Gateway::Listener gatewayListener;

	HardwareManager::ResponseListener responseListener;
public:
	Device::wPtr getDevice(uint32_t gateway, uint32_t hub, uint32_t device) {
		uint32_t type = deviceMapping[gateway][hub][device];
		return devices[type];
	}

	Impl(gumyns::sh::config::Config & config, gumyns::sh::DatabaseService::wPtr database)
			: hubFactory(new GatewayFactory(config.hubPluginPath())), deviceFactory(new DeviceFactory(config.devicePluginPath()))  {
		this->gatewayListener = [this](Gateway& gateway, uint32_t hubAddress, std::vector<uint8_t> frame){
			LogD << "<----" << toHexString(frame) << std::endl;
			if(frame[0] >> 5 == 0) { // Identification response...
				uint16_t type = (frame[1] << 8) + frame[2];
				deviceMapping[gateway.getId()][hubAddress][frame[0] & 0x1F] = type;
				LogD << "Setup device [" << gateway.getId() << "][" << hubAddress << "][" << (frame[0] & 0x1F) << "]=" << type << std::endl;
				if (responseListener) {
					nlohmann::json json;
					json["gateway"] = gateway.getId();
					json["hub"] = hubAddress;
					json["device"] = frame[0] & 0x1F;
					json["order"] = (int) (frame[0] >> 5);
					responseListener(json);
				}
			} else {// Any other
				if (auto parser = getDevice(gateway.getId(), hubAddress, static_cast<uint32_t>(frame[0] & 0x1F)).lock()) {
					if (responseListener) {
						nlohmann::json json = parser->response(frame);
						json["gateway"] = gateway.getId();
						json["hub"] = hubAddress;
						json["device"] = frame[0] & 0x1F;
						json["order"] = (int) (frame[0] >> 5);
						responseListener(json);
					}
				}
			}
		};
		if (auto db = database.lock()) {
			{
				auto gateways = db->getGateways();
				auto it = gateways.begin();
				while (it != gateways.end()) {
					nlohmann::json &gateway = *it++;
					LogD << "Adding gateway: " << gateway << std::endl;
					PluginDescriptor descriptor(gateway);
					loadHub(gateway["id"], descriptor);
				}
			}
			{
				auto parsers = db->getParsers();
				auto it = parsers.begin();
				while (it != parsers.end()) {
					nlohmann::json &parser = *it++;
					LogD << "Adding Parser: " << parser << std::endl;
					PluginDescriptor descriptor(parser);
					loadParser(parser["type"], descriptor);
				}
			}
		}
	}

	~Impl() {}

	std::string toHexString(std::vector<uint8_t> vector) {
		std::stringstream builder;
		auto it = vector.begin();
		builder << "[ ";
		while (it != vector.end())
			builder << std::hex << std::setfill('0') << std::setw(2) << (int)*it++ << " ";
		builder << "]";
		return builder.str();
	}

	void setResponseListener(const ResponseListener &responseListener) {
		this->responseListener = responseListener;
	}

	void write(nlohmann::json request) {
		if (auto parser = getDevice(request["gateway"], request["hub"], request["device"]).lock()) {
			// Check if request contains specific request
			if (request.find("request") != request.end()) {
				uint32_t address = request["device"];
				nlohmann::json order = request["request"];
				LogD << "--->" << address << ", " << order << " and " << parser->getId() << std::endl;
				auto input = parser->request(address, order);
				LogD << "---->" << toHexString(input) << std::endl;
				gateways[request["gateway"]]->write(request["hub"], input);
			} else { // If request unspecified - make identification
				gateways[request["gateway"]]->identify(request["hub"]);
			}
		} else { // If parser doesn't exists - make identification
			gateways[request["gateway"]]->identify(request["hub"]);
		}
	}

	void loadHub(uint32_t id, PluginDescriptor &descriptor) {
		auto hub = hubFactory->create(descriptor);
		gateways.insert(std::make_pair(id, Gateway::sPtr(new Gateway(id, hub, this->gatewayListener))));
	}

	void loadParser(uint32_t id, PluginDescriptor &descriptor) {
		auto parser = deviceFactory->create(descriptor);
		devices.insert(std::make_pair(id, Device::sPtr(new Device(id, parser))));
	}
};

gumyns::sh::HardwareManager::HardwareManager(gumyns::sh::config::Config &config, gumyns::sh::DatabaseService::wPtr db)  : pImpl(new gumyns::sh::HardwareManager::Impl(config, db)) {}

gumyns::sh::HardwareManager::~HardwareManager() {}

void gumyns::sh::HardwareManager::setResponseListener(const gumyns::sh::HardwareManager::ResponseListener &listener) {
	pImpl->setResponseListener(listener);
}

void gumyns::sh::HardwareManager::write(nlohmann::json request) {
	pImpl->write(request);
}

