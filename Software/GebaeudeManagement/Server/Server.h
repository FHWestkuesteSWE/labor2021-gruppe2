#pragma once

class Server
{
public:
	void start(char port[]);
	Server();
	~Server();

protected:
	virtual void processRequest(char request[], char answer[]);
};

