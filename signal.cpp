#include <iostream> 
#include <csignal> 
#include <unistd.h> 

void Sighandler (int sigNum) {
	std::cout << "\nInterrupt signal(" << sigNum << ") received.\n";
       	exit(sigNum);	
}

int main () {
	//register a signal 
	signal(SIGINT, Sighandler);
	std::cout << "Press Ctrl + C to trigger a signal" << std::endl;

	while (1) {
		std::cout << "Running ..." << std::endl;
		sleep(2); 
	}

	return 0;
}
