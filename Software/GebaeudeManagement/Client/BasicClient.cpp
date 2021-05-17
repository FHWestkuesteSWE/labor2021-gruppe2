#include "BasicClient.h"


BasicClient::BasicClient(char _server[], char _port[]) {
	server = _server;
	port = _port;
}
void BasicClient::sendRequest(const char request[], char answer[]) {
	boost::asio::io_service io_service;

	tcp::resolver resolver(io_service);
	tcp::resolver::query query(tcp::v4(), server, port);
	tcp::resolver::iterator iterator = resolver.resolve(query);

	tcp::socket s(io_service);
	boost::asio::connect(s, iterator);

	size_t request_length = strlen(request)+1;
	boost::asio::write(s, boost::asio::buffer(request, request_length));

	size_t reply_length = boost::asio::read(s,
		boost::asio::buffer(answer, max_length));
}
BasicClient::~BasicClient() {

}
