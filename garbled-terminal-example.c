#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 

char str[] = "$";

int main (int argc, char* argv[]) {
	
	int i; 
	char output[6000]; 
	for (i = 0; i < 10; i++) {
		switch (fork()){
			case 0: 
				int k; 
				for (k = 0; k + 1 < 6000; ++k) output[k] = (char) ('a' + i);
			     	output[6000 - 1] = '\n';
				write (1, output, sizeof(output));
				exit(0);
			case -1: 
				exit(0);
			default: 
				break;	
		}
	}
	sleep(2);

	return 0; 
}
