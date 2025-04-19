#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <signal.h> 
#include <termio.h> 
#include <sys/select.h> 

int main (int argc, char* argv[]) {
	
	fd_set rfd; 
	struct timeval timeout; 

	FD_ZERO (&rfd); 
	FD_SET (STDIN_FILENO, &rfd); 

	timeout.tv_sec = 5; 
	timeout.tv_usec = 0; 

	printf("Waiting for input (5 seconds timeout) ... \n"); 

	int result = select (STDIN_FILENO + 1, &rfd, NULL, NULL, &timeout); 

	if (result == -1) {
		perror("select()"); 
	} else if (result == 0) {
		printf("Timeout! No input. \n");
	} else if (FD_ISSET(STDIN_FILENO, &rfd)) {
		char buf[100]; 
		read(STDIN_FILENO, buf, sizeof(buf)); 
		printf("Input received: %s \n", buf);
	}

	return 0; 
}
