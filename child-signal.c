#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <signal.h>

int main (int argc, char* argv[]) {
	
	char Buf[256]; 
	
	if (argc != 1) {
		signal(SIGCLD, SIG_IGN); 
	}
	
	while (read(0, Buf, 256)){
		if (fork() == 0) {
			printf("Created a child with pid=%d and Buf:  %s \n", getpid(), Buf);
			
			exit(0);
		}
	}
	
	return 0; 
}
