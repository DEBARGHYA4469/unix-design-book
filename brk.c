#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <signal.h> 

char* cptr; 
int CallNo; 

int main (int argc, char* argv[]) {
	
	extern void catcher();
		
	signal (SIGSEGV, catcher); 

	cptr = sbrk (0); 
	printf("Original Brk value=%u", cptr); 

	for (;;) 
		*cptr++ = 1; 

	return 0; 
}

void catcher(int Signal) {
	CallNo++;
	printf("Caught Sig %d in %dth call at addr %u \n", Signal, CallNo, cptr);
	sbrk(256); 
	signal(SIGSEGV, catcher);
}
