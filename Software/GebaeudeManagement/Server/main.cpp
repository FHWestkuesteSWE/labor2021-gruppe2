#include "BasicServer.h"

//int main(int argc, char* argv[]) {
int main() {
	BasicServer s;
	// Define Port
	char server_port[] = "5000";
	// Init Light Simulation
	s.beleuchtungInit();
	s.getLightInfo();

	//s.start(argv[1]);
	// Start Server on Port %serverPort%
	std::cout << "Server will start on IP: 127.0.0.1 and PORT: " << server_port << std::endl;
	s.start(server_port);

	return 0;
}