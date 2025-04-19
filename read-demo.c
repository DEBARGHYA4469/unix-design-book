#include <unistd.h> 
#include <fcntl.h> 
#include <stdio.h> 

int main () {
	int fd; 
	char lil[2], big[4]; 
	fd = open("hello", O_RDONLY);
	read(fd, lil, 2);
	read(fd, big, 4);
	printf("Small array"); 
	printf(" %c %c \n", lil[0], lil[1]);
	printf("Big array ");
	printf("%c %c %c %c \n", big[0], big[1], big[2], big[3]);
	close(fd); 
	return 0;
} 
