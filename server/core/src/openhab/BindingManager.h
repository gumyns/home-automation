#ifndef GUMYNS_SMART_HOME_BINDINGMANAGER_H
#define GUMYNS_SMART_HOME_BINDINGMANAGER_H

#include <utils/utils.h>

namespace gumyns {
namespace sh {
	class BindingManager {
	PIMPL(BindingManager)
	public:
		BindingManager();

		uint64_t add(const uint8_t *frame, size_t size);

		std::string byAddress(uint64_t);

		uint64_t byBinding(std::string&);

		virtual ~BindingManager();
	};
}
}



#endif //GUMYNS_SMART_HOME_BINDINGMANAGER_H
