#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <signal.h> 
#include <termio.h> 

struct termio savetty; 

int main (int argc, char* argv[]) {
	
	extern void sigcatch(); 
	struct termio newtty; 
	int nrd; 
	char buf[32]; 
	signal(SIGINT, sigcatch); 
	
	if (ioctl(0, TCGETA, &savetty) == -1) {
		printf("ioctl failed: not a tty \n"); 
		exit(0);
	}

	newtty = savetty;
	newtty.c_lflag &= ~ICANON; 
	newtty.c_lflag &= ~ECHO; 
	newtty.c_cc[VMIN] = 5; 
	newtty.c_cc[VTIME] = 100; 
	
	if (ioctl(0, TCSETAF, &newtty) == -1) {
		printf("cannot put tty into raw mode \n");
		exit(0);
	}
	
	for (;;) {
		nrd = read (0, buf, sizeof(buf));
		buf[nrd] = 0; 
		printf("read %d chars %s \n", nrd, buf);
	}

	return 0; 
}

void sigcatch () {
	ioctl(0, TCSETAF, &savetty);
	exit(0);
}


