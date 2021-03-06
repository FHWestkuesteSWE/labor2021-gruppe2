#define _CRT_SECURE_NO_WARNINGS
#include "BasicServer.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <cstring>
#include <iterator>


BasicServer::~BasicServer()
{
}

BasicServer::BasicServer()
{
	for (int x = 0; x < 100; x++) {
		server_beleuchtung_[x] = false;
	}
}

void BasicServer::session(socket_ptr sock)
{
	try
	{
		int cycleCounter = 0;
		for (;;)
		{
			// Data gethering cicle
			if (cycleCounter >= 500) {
				getLightInfo();
				cycleCounter = 0;
			}

			char request[BasicServer::max_length_] = { 0 };
			char answer[BasicServer::max_length_] = { 0 };
			boost::system::error_code error;
			// size_t length = sock->read_some(boost::asio::buffer(request), error);
			sock->read_some(boost::asio::buffer(request), error);
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.
			this->processRequest(request,answer);
			boost::asio::write(*sock, boost::asio::buffer(boost::asio::buffer(answer), max_length_));
			cycleCounter++;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void BasicServer::start(char port[]) {
	boost::asio::io_service io_service;

	using namespace std; // For atoi.
	using boost::asio::ip::tcp;
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), static_cast<boost::asio::ip::port_type>(atoi(port))));
	for (;;)
	{
		socket_ptr sock(new tcp::socket(io_service));
		a.accept(*sock);
		boost::thread t(boost::bind(&BasicServer::session, this, sock));
	}
}

//---------------------------------------------------------------
// General PLC Functions
// Server Answer Management
void BasicServer::processRequest(char req[], char ans[]) {
	if (strcmp(req, "LightOff") == 0) {
		// Suffix aendern, oder static_cast
		// strncpy(ans, "Beleuchtung wird ausgeschaltet\0", std::min<int>(max_length, strlen(ans) + 1ull));
		// strncpy(ans, "Beleuchtung wird ausgeschaltet\0", std::min<int>(max_length, strlen(ans) + static_cast<size_t>(1)));
		strncpy(ans, "Beleuchtung wird ausgeschaltet\0", static_cast<size_t>(max_length_));
		//ans[strlen(ans) - 1] = 0;
		// Turn of every Light
		turnOffAllLight();
	}
	else if (strcmp(req, "getLightInfo") == 0) {
		
		char dataString[BasicServer::max_length_] = "\0"; // ggf. Dynamischer machen
		getLightInfo();
		for (int x = 0; x < std::size(server_beleuchtung_); x++) {
			if (server_beleuchtung_[x]) dataString[x] = '1';
			else dataString[x] = '0';
			dataString[x + 1] = '\0';
		}
		strncpy(ans, dataString, static_cast<size_t>(max_length_));
	}
	else {
		strncpy(ans, "Unbekannter Befehl\0", static_cast<size_t>(max_length_));
	}

}

// Function to turn of every light in the given building
void BasicServer::turnOffAllLight() {
	for (int x = 0; x < std::size(server_beleuchtung_); x++) {
		beleuchtungs_zustaende_[x] = false;
	}
}
// Function to get Information about every Light in the given Building
void BasicServer::getLightInfo() {
	for (int x = 0; x < std::size(beleuchtungs_zustaende_); x++) {
		server_beleuchtung_[x] = beleuchtungs_zustaende_[x];
	}
}


//----------------------------------------------------------------
// Light simulation functions
void BasicServer::beleuchtungInit() {
	srand(static_cast<unsigned int>(time(NULL)));
	for (int x = 0; x < std::size(beleuchtungs_zustaende_); x++) {
		if ((rand() % 2) > 0) beleuchtungs_zustaende_[x] = true;
		else beleuchtungs_zustaende_[x] = false;
	}
}



// ----------------------------------------------------------------
// Clientfunctions
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

	//size_t reply_length = boost::asio::read(s,boost::asio::buffer(answer, max_length));
	boost::asio::read(s, boost::asio::buffer(answer, max_length_));

}
