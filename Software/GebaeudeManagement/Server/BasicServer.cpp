#define _CRT_SECURE_NO_WARNINGS
#include "BasicServer.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <cstring>

void BasicServer::session(socket_ptr sock)
{
	try
	{
		for (;;)
		{
			char request[BasicServer::max_length];
			char answer[BasicServer::max_length];
			boost::system::error_code error;
			size_t length = sock->read_some(boost::asio::buffer(request), error);
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.
			this->processRequest(request,answer);
			boost::asio::write(*sock, boost::asio::buffer(boost::asio::buffer(answer), max_length));
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
		strncpy(ans, "Beleuchtung wird ausgeschaltet\0", std::min<int>(max_length, strlen(ans) + 1));
	}
	else {
		strncpy(ans, "Unbekannter Befehl\0", std::min<int>(max_length, strlen(ans) + 1));
	}

}

BasicServer::~BasicServer()
{
}

// Beleuchtungsfunktionen
void BasicServer::beleuchtungInit() {

}






void BasicServer::sendRequest(const char request[], char answer[]) {
	char beleuchtungIPAdresse[] = "127.0.0.1";
	char beleuchtungPort[] = "5001";
	boost::asio::io_service io_service;

	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), beleuchtungIPAdresse, beleuchtungPort);
	boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

	boost::asio::ip::tcp::socket s(io_service);
	boost::asio::connect(s, iterator);

	size_t request_length = strlen(request) + 1;
	boost::asio::write(s, boost::asio::buffer(request, request_length));

	size_t reply_length = boost::asio::read(s,boost::asio::buffer(answer, max_length));
}
