#include "Server.h"

int main(int argc, char* argv[]) {
	Server s;
	s.start(argv[1]);
	return 0;
}