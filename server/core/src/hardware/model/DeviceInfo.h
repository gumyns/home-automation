#ifndef GUMYNS_SMART_HOME_DEVICEINFO_H
#define GUMYNS_SMART_HOME_DEVICEINFO_H

#include <utils/utils.h>

namespace gumyns{
namespace sh {

	class DeviceInfo {
		POINTERS(DeviceInfo)
	public:
		uint32_t getDeviceId() {return 0;}
	};

}}

#endif //GUMYNS_SMART_HOME_DEVICEINFO_H
