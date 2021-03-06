#define _CRT_SECURE_NO_WARNINGS
#include "BasicServer.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

void BasicServer::session(socket_ptr sock)
{
	try
	{
		for (;;)
		{
			char request[BasicServer::max_length_];
			char answer[BasicServer::max_length_];
			boost::system::error_code error;
			size_t length = sock->read_some(boost::asio::buffer(request), error);
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.
			this->processRequest(request,answer);
			boost::asio::write(*sock, boost::asio::buffer(boost::asio::buffer(answer), max_length_));
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}
BasicServer::BasicServer()
{

}

void BasicServer::start(char port[]) {
	boost::asio::io_service io_service;

	using namespace std; // For atoi.
	using boost::asio::ip::tcp;
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), atoi(port)));
	for (;;)
	{
		socket_ptr sock(new tcp::socket(io_service));
		a.accept(*sock);
		boost::thread t(boost::bind(&BasicServer::session, this, sock));
	}
}

/*
Simple Server: just replies by echoing
*/
void BasicServer::processRequest(char req[], char ans[]) {
	if (strcmp(req, "LightOff") == 0) {
		strncpy(ans, "Beleuchtung wird ausgeschaltet\0", static_cast<size_t>(max_length_));

	}
	else {
		strncpy(ans, "Unbekannter Befehl\0", static_cast<size_t>(max_length_));
	}

}

BasicServer::~BasicServer()
{
}
