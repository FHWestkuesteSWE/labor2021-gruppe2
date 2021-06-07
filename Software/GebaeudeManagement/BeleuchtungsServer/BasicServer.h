#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

class BasicServer
{
public:
	void start(char port[]);
	BasicServer();
	~BasicServer();
	const static int max_length_=1024;

private:
	void session(socket_ptr sock);
	virtual void processRequest(char request[], char answer[]);
};

