#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <signal.h> 

void sigcatcher(){
	printf("PID %d caught one\n", getpid());
	signal(SIGINT, sigcatcher);
}

int main () {
	
	int ppid; 
	signal (SIGINT, sigcatcher); 
	
	if (fork() == 0) {
		sleep(5); 
		ppid = getppid(); 
		for(;;) {
			if (kill(ppid, SIGINT) == -1){
				printf("Killing PPID: %d went wrong", ppid);
				exit(0);
			}
		}
	}
	
	nice(10); 
	for(;;) 	

	return 0;
}
