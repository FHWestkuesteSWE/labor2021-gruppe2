#pragma once

class Client
{
public:
	Client(char server[], char port[]);
	void sendRequest(const char request[], char answer[]);
	~Client();
protected:

}; 
