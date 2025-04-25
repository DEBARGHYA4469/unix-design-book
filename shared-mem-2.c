#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <sys/types.h> 

#define SHMKEY 75 
#define K 1024 

int shmid; 

int main (int argc, char* argv[]) {
	
	int i, *pint; 
	char* addr; 
	
	shmid = shmget (SHMKEY, 64 * K, 0777);
	addr = shmat (shmid, 0, 0); 
	pint = (int *) addr; 

	while (*pint == 0);
	for (i = 0; i < 256; i++)
		printf("%d\n", *pint++);	

	return 0; 
}
