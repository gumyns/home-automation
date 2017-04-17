
#include "DatabaseService.h"
#include <modern_sqlite/hdr/sqlite_modern_cpp.h>

class gumyns::sh::DatabaseService::Impl {
	std::unique_ptr<sqlite::database> db;
public:
	Impl(std::string name) : db(new sqlite::database(name.c_str()) ) {
        (*db.get()) << "CREATE TABLE IF NOT EXISTS `gateways` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, `type` INTEGER NOT NULL, `name` TEXT NOT NULL, `config` TEXT );";
		(*db.get()) << "CREATE TABLE IF NOT EXISTS `parsers` ( `type` INTEGER NOT NULL PRIMARY KEY UNIQUE, `name` TEXT NOT NULL, `alias_name` TEXT NOT NULL, `config` TEXT );";
	}

	std::vector<nlohmann::json> getGateways() {
		std::vector<nlohmann::json> gateways;
        (*db.get()) << "select id, type, name, config from gateways;"
                    >> [&](int id, int type, std::string name, std::string config) {
						nlohmann::json json;
						json["id"] = id;
						json["type"] = type;
                        json["name"] = "." + name;
						json["configuration"] = nlohmann::json::parse(config);
						gateways.push_back(json);
					};
		return gateways;
	}

	std::vector<nlohmann::json> getParsers() {
		std::vector<nlohmann::json> gateways;
        (*db.get()) << "select type, name, config from parsers;"
                    >> [&](int type, std::string name, std::string config) {
						nlohmann::json json;
						json["type"] = type;
                        json["name"] = "." + name;
						json["configuration"] = nlohmann::json::parse(config);
						gateways.push_back(json);
					};
		return gateways;
	}

	gumyns::sh::DeviceInfo::uPtr queryDevice(int dId) {
		gumyns::sh::DeviceInfo::uPtr device;
		(*db.get()) << "select id, hubId, addr, type, permission, ttl, name from devices where id=?;"
					<< dId
					>> [&](int id, int hubId, int addr, int type, int permission, int ttl, std::string name) {
//						device.reset(new gumyns::sh::DeviceInfo((uint32_t) hubId, (uint32_t) id, (uint8_t) addr, type,  permission, (uint32_t) ttl, name));
					};
		return device;
	}
};

//
//std::vector<socket::Socket::s_ptr> DatabaseService::querySockets() {
//    std::vector<socket::Socket::s_ptr> sockets;
//    (*db.get()) << "select id, addr, type, address, name from sockets;"
//                >> [&](int id, int addr, int type, std::string address, std::string name) {
//                    sockets.push_back(socket::Socket::s_ptr(new socket::Socket((uint32_t) id, (uint8_t) addr, (socket::Type) type, address, name)));
//                };
//    return sockets;
//}
//
//socket::Socket::u_ptr DatabaseService::querySocket(int pId) {
//    socket::Socket::u_ptr socket;
//    (*db.get()) << "select id, addr, type, address, name from sockets where id=?;"
//                << pId
//                >> [&](int id, int addr, int type, std::string address, std::string name) {
//                    socket.reset(new socket::Socket((uint32_t) id, (uint8_t) addr, (socket::Type) type, address, name));
//                };
//    return socket;
//}
//
//std::vector<HubInfo::s_ptr> DatabaseService::queryHubs() {
//    std::vector<HubInfo::s_ptr> hubs;
//    (*db.get()) << "select id, pAddr, dAddr, type, socketId, name from hubs;"
//                >> [&](int id, int pAddr, int dAddr, int type, int socketId, std::string name) {
//                    hubs.push_back(HubInfo::s_ptr(new HubInfo((uint32_t) id, (uint8_t) dAddr, (uint32_t) pAddr, (uint32_t) socketId, (socket::Type) type, name)));
//                };
//    return hubs;
//}
//
//HubInfo::u_ptr DatabaseService::queryHub(int hId) {
//    HubInfo::u_ptr hub;
//    (*db.get()) << "select id, pAddr, dAddr, type, socketId, name from hubs where id=?;"
//                << hId
//                >> [&](int id, int pAddr, int dAddr, int type, int socketId, std::string name) {
//                    hub.reset(new HubInfo((uint32_t) id, (uint8_t) pAddr, (uint32_t) dAddr, (uint32_t) socketId, (socket::Type) type, name));
//                };
//    return hub;
//}
//
//std::vector<DeviceInfo::s_ptr> DatabaseService::queryDevices() {
//    std::vector<DeviceInfo::s_ptr> devices;
//    (*db.get()) << "select id, hubId, addr, type, permission, ttl, name from devices;"
//                >> [&](int id, int hubId, int addr, int type, int permission, int ttl, std::string name) {
//                    devices.push_back(DeviceInfo::s_ptr(new DeviceInfo((uint32_t) hubId, (uint32_t) id, (uint8_t) addr, (DeviceType) type, (DevicePermission) permission, (uint32_t) ttl, name)));
//                };
//    return devices;
//}

gumyns::sh::DeviceInfo::uPtr gumyns::sh::DatabaseService::queryDevice(int dId) {
    return pImpl->queryDevice(dId);
}


gumyns::sh::DatabaseService::sPtr gumyns::sh::DatabaseService::create(std::string name) {
	return gumyns::sh::DatabaseService::sPtr(new DatabaseService(name));
}

gumyns::sh::DatabaseService::DatabaseService(std::string name) : pImpl(new Impl(name)) {}

gumyns::sh::DatabaseService::~DatabaseService() {}

std::vector<nlohmann::json> gumyns::sh::DatabaseService::getGateways() {
	return pImpl->getGateways();
}

std::vector<nlohmann::json> gumyns::sh::DatabaseService::getParsers() {
	return pImpl->getParsers();
}

