#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <json.hpp>


class Connector final {
public:
	typedef std::function<void(uint8_t)> Listener;
private :
	boost::asio::io_service service;

	boost::thread_group threads;

	std::unique_ptr<boost::asio::serial_port> port;

	Listener listener;
public:

	Connector(nlohmann::json & param, Listener);

	void write(std::vector<uint8_t> &) ;

	virtual ~Connector();
};

#endif //CONNECTOR_H
