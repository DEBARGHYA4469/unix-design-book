#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 

int main () {
	int i,j; 
	char Buf1[4], Buf2[4]; 

	i = open ("in", O_RDONLY); 
	j = dup(i); 
	
	read (i, Buf1, 2); 
	read (j, Buf2, 2); 

	close (i); 

	//read (j, Buf2, 2);

	printf("Printing the contents of Buf1 %c %c \n", Buf1[0], Buf1[1]); 	
	printf("Printing the contents of Buf2 %c %c %c %c \n", Buf2[0], Buf2[1], Buf2[2], Buf2[3]);
		
	return 0; 
} 
