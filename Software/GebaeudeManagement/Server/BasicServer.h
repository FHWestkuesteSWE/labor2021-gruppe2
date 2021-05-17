#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>


typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

class BasicServer
{
public:
	// Server Funktionen
	void start(char port[]);
	BasicServer();
	~BasicServer();
	const static int max_length=1024;

	// Client Funktionen
	void sendRequest(const char request[], char answer[]);

	// Prozessleitfunktion
	bool serverbeleuchtung[100];

	//Beleuchtungssystem
	bool beleuchtungsZustaende[100];
	void beleuchtungInit();



private:
	void session(socket_ptr sock);
	virtual void processRequest(char request[], char answer[]);
};

