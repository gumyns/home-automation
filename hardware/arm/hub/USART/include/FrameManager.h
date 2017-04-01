#ifndef FRAMEMANAGER_H_
#define FRAMEMANAGER_H_

#include <queue>
#include <lib/Frame.h>

class FrameManager {
public:
	enum Mode { READING, WRITING };
protected:
	Mode mode = WRITING;

	std::queue<::gumyns::sh::Frame *> frames;
public:
	FrameManager() = default;

	virtual ~FrameManager() {};

	virtual void onFrameReceived(::gumyns::sh::Frame *) = 0;

	virtual void process() = 0;

	virtual void identify() = 0;
};

#endif /* FRAMEMANAGER_H_ */
