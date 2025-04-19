#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 

char input[200];

int main (int argc, char* argv[]) {
	
	register int i; 
	for (i = 0; i < 20; i++) {
		switch(fork()) {
			case -1:
				exit(0);
			default:
				break;
			case 0:
				int k;
				for (k = 0; k < 4; ++k) {
					read(0, input, 3);
					printf("Process %d read %s \n", i, input);
				}
				exit(0);
		}
	}
	while(1) {} 
	return 0; 
}
