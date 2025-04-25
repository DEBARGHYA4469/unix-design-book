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
	char *addr1, *addr2; 
	extern void cleanup(); 

	for (i = 0; i < 20; i++) signal (i, cleanup); 
	
	// allocate shared memory 
	shmid = shmget (SHMKEY, 128*K, 0777 | IPC_CREAT);
	
	addr1 = shmat(shmid, 0, 0); // map - 1
	addr2 = shmat(shmid, 0, 0); // map - 2 

	printf("addr1 0x%x addr2 0x%x\n", addr1, addr2);
	pint = (int *) addr1;

	for (i = 0; i < 256; i++){
		*pint++ = i; // write to map - 1
	}

	pint = (int *) addr1; 
	*pint = 256; 

	pint = (int *) addr2; // read from map - 2
	for (i = 0; i < 256; i++)
		printf("index %d\tvalue %d\n", i, *pint++);
	
	pause();
	
	return 0; 
}

void cleanup(){
	shmctl (shmid, IPC_RMID, 0);
	exit(0);
}
