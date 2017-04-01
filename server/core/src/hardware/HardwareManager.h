#ifndef GUMYNS_SMART_HOME_HARDWAREMANAGER_H
#define GUMYNS_SMART_HOME_HARDWAREMANAGER_H

#include <utils/utils.h>
#include <json.hpp>
#include <config/Config.h>
#include <hardware/model/Gateway.h>
#include <hardware/model/Device.h>
#include <database/DatabaseService.h>
#include <zmq.hpp>

namespace gumyns {
namespace sh {

	class HardwareManager {
		PIMPL(HardwareManager)

	public:
		typedef std::function<void(nlohmann::json)> ResponseListener;

		HardwareManager(gumyns::sh::config::Config &, DatabaseService::wPtr);

		void setResponseListener(const ResponseListener &);

		void write(nlohmann::json request);

		~HardwareManager();
	};

}}

#endif //GUMYNS_SMART_HOME_HARDWAREMANAGER_H
