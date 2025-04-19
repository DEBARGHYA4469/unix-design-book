#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <signal.h> 
#include <termio.h> 

int main (int argc, char* argv[]) {
	
	register int i, n; 
	int fd; 
	char buf[256]; 

	if ((fd = open("/dev/tty", O_RDONLY | O_NDELAY)) == -1) exit(0);

	n = 1; 
	for (;;) {
		for (i = 0; i < n; ++i) {
			if (read(fd, buf, sizeof(buf)) > 0) {
				printf("read %s at n %d \n", buf, n);
				n--;
			}
			else n++;
		}
	}

	return 0; 
}
