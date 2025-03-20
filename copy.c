#include <fcntl.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>

char buf[2048]; 

int main (int argc, char* argv[]){
	int fd_old, fd_new; 
	if (argc != 3) {
		printf("Need 2 arguments to copy program\n");
		exit(1); 
	}
	fd_old = open (argv[1], O_RDONLY); 
	if (fd_old == -1){
		printf("Cannot open file %s\n", argv[1]);
		exit(1); 
	}
	fd_new = creat(argv[2], 0666);
	if (fd_new == -1) {
		printf("Cannot create file %s\n", argv[2]);
		exit(1); 
	}
	// copy code 
	
	int count;
       	while ((count = read(fd_old, buf, sizeof(buf))) > 0) 	
		write(fd_new, buf, count);
	exit(0); 	
} 
