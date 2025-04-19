#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <signal.h>

void f(int n) {
	printf("Voila"); 
} 

int main (int argc, char* argv[]) {
	
	signal (SIGBUS, f);
	char *c = (char *) malloc(10); // 10 bytes of mem 
	int* v = (int *)(c + 2); // misaligned 
	*v = 22; 
		
	return 0; 
}
