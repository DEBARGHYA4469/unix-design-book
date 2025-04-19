#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <signal.h> 

int main (int argc, char* argv[]) {
	
	int i, *ip; 
	extern void f(); 
	extern void sigcatch(); 

	ip = (int *) (&f); 

	for (i = 0; i < 20; i++) signal(i, sigcatch); 
	*ip = 1; // illegal access of text region 	

	printf("after assign to ip\n"); 
	f(); 

	return 0; 
}

void f() {} 

void sigcatch(int n) {
	printf("caught sig %d \n", n); 
	exit(1); 
}
