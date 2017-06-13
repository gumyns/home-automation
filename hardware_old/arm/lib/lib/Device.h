#ifndef DEVICEFRAME_H_
#define DEVICEFRAME_H_

#include <stdio.h>
#include <functional>
#include <queue>
#include "Frame.h"
#include "Buffer.h"
#include "Socket.h"

namespace gumyns {
namespace sh {
/**
 * Interface needed for implementation of device specific features.
 */
class Device {
protected:
//	std::queue<Frame *> requests, responses;
public:
	Device() = default;

	/** Once process returns true, this method will be called. Prepare response frame here. */
	virtual Frame *read() = 0;

	/** Once frame arrives from hub, it goes here. Long operations should be handled in process method, as this one is called via interrupt */
	virtual void write(Frame *) = 0;

	/**
	 * Implement long time operations here, device specific logic, communication with peripherals  etc. Called periodically.
	 * If device have something to send back to hub, it must return 'true'
	 */
	virtual bool process() = 0;

	virtual ~Device() {
	}
};

}
}

#endif /* DEVICEFRAME_H_ */
