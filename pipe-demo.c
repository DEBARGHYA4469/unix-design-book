#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h> 


char str[] = "Hello"; 

int main () {

	char Buf[1024]; 
	char *cp1, *cp2;

	int fds[2]; 
	
	cp1 = str; 
	cp2 = Buf; 

	while (*cp1) *cp2++ = *cp1++; // Fill in the buffer 
	Buf[5] = '\0';
	printf("Printing out the buffer: %s\n", Buf); 
       	
	pipe (fds); // create a unnamed pipe with file descriptors fds[0], fds[1] 
	while(1) {
		write (fds[1], Buf, 6); 
		read (fds[0], Buf, 6); 
		printf("Printing out the buffer(pipe out) %s\n", Buf); 
	}
	
	return 0; 
}
