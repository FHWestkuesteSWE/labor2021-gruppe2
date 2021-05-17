#include "BasicServer.h"

int main(int argc, char* argv[]) {
	BasicServer s;
	char serverPort[] = "5000";
	//s.start(argv[1]);
	s.start(serverPort);

	return 0;
}