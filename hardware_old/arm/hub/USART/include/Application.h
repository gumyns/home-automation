#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <lib/Parser.h>
#include <FrameManager.h>
#include <DeviceParser.h>
#include <BlinkLed.h>
#include <Timer.h>

class Application {
	::gumyns::sh::Parser *extParser;
	::gumyns::sh::Parser *devParser;

	FrameManager * frameManager;

	int divider = 1;

	Timer timer;

public:
	Application(::gumyns::sh::Parser *, DeviceParser *);

	virtual ~Application();

	void main();

	::gumyns::sh::Socket::IRQ extIRQ();

	::gumyns::sh::Socket::IRQ devIRQ();
};

#endif /* APPLICATION_H_ */
