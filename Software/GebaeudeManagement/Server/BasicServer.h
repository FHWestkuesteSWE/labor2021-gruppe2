#pragma once

// Boots Libs
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>

// Other Libs
#include <iostream>


typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

class BasicServer
{
public:
	// Server Funktionen
	void start(char port[]);
	BasicServer();
	~BasicServer();
	const static int max_length_=1024;

	// Client Funktionen
	void sendRequest(const char request[], char answer[]);

	// Prozessleitfunktion
	bool server_beleuchtung_[100]{ 0 };
	void turnOffAllLight();
	void getLightInfo();

	// Beleuchtungssystem
	// Als neue Klasse konstruieren
	bool beleuchtungs_zustaende_[100]{ 0 };
	void beleuchtungInit();
	



private:
	void session(socket_ptr sock);
	virtual void processRequest(char request[], char answer[]);
};

