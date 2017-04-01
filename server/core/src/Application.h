#ifndef GUMYNS_SMART_HOME_APPLICATION_H
#define GUMYNS_SMART_HOME_APPLICATION_H

#include <utils/utils.h>

namespace gumyns {
namespace sh{

	class Application {
		PIMPL(Application)
		Application();
	public:
		virtual ~Application();

		static Application::uPtr create();

		int run(int, char **);
	};

}}

#endif //GUMYNS_SMART_HOME_APPLICATION_H
