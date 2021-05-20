#include "BasicServer.h"

int main(int argc, char* argv[]) {
	BasicServer s;
	// Define Port
	char serverPort[] = "5000";
	// Init Light Simulation
	s.beleuchtungInit();
	s.getLightInfo();

	//s.start(argv[1]);
	// Start Server on Port %serverPort%
	std::cout << "Server will start on IP: 127.0.0.1 and PORT: " << serverPort << std::endl;
	s.start(serverPort);

	return 0;
}