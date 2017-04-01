#ifndef SMARTHOMESERVER_DATABASESERVICE_H
#define SMARTHOMESERVER_DATABASESERVICE_H

#include <utils/utils.h>
#include <json.hpp>
#include <hardware/model/DeviceInfo.h>

namespace gumyns{
namespace sh {

	class DatabaseService {
		PIMPL(DatabaseService)
		DatabaseService(std::string);
	public:
		~DatabaseService();

		static sPtr create(std::string);

		std::vector<nlohmann::json> getGateways();

		std::vector<nlohmann::json> getParsers();
//
//    std::vector<socket::Socket::s_ptr> querySockets();
//
//    socket::Socket::u_ptr querySocket(int);
//
//    std::vector<HubInfo::s_ptr> queryHubs();
//
//    HubInfo::u_ptr queryHub(int);
//
//    std::vector<DeviceInfo::s_ptr> queryDevices();
//
		DeviceInfo::uPtr queryDevice(int);
	};

}}

#endif //SMARTHOMESERVER_DATABASESERVICE_H
