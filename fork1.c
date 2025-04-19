#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <signal.h>

int main (int argc, char* argv[]) {
	
	for (int i = 0; i < 6; i++) {
		if (fork() == 0) {
			printf("Hello from child, %d \n", i);
			pause();
		}

	}	
	kill (0, SIGINT);

	return 0; 
}
