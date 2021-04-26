#define _CRT_SECURE_NO_WARNINGS
#include "Server.h"
#include <string.h>
#include <algorithm>

Server::Server()
{

}

void Server::start(char port[]) {

}

void Server::processRequest(char req[], char ans[]) {
	strncpy(ans, req, std::min<int>(1024, strlen(ans) + 1));
}

Server::~Server()
{
}
