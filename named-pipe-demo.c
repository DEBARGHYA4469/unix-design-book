#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 

char str[] = "Hello"; 

int main (int argc, char* argv[]) {
	
	int fd; 
	char Buf[256]; 
	
	// create a named pipe called fifo 
	mknod ("Fifo", 010777, 0); 
	if (argc == 2)
		fd = open ("Fifo", O_WRONLY); 
	else 
		fd = open ("Fifo", O_RDONLY);

	if (argc == 2)
		write (fd, str, 6); 
	else {
		read (fd, Buf, 6); 
		printf("Reading from the PIPE %s", Buf);	
	}

	return 0; 
}
