#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 

int x = 1234; 

int main (int argc, char* argv[]) {

	
	printf("address of x is %0x\n", &x);
	printf("%d\n", x); 

	return 0; 
}
