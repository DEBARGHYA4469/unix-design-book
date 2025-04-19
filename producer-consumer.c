#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <pthread.h>


#define BUF_SIZE 5 
int Buf[BUF_SIZE]; 
int Count; 
int In, Out; 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER; 

void* producer (void *arg) { // 'N' producer
	int id = *(int *) arg; 

	while (1) {
		int x = rand() % 10; // a random number produced 
		pthread_mutex_lock(&mutex);
		while (Count == BUF_SIZE) pthread_cond_wait(&not_full, &mutex); // use while against spurious release 
		Buf[(++In) % BUF_SIZE] = x;
		Count++;
		printf("Producer %d: Added item %d to the buffer \n", id, x);
		pthread_cond_signal(&not_empty);	
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void* consumer (void *arg) {
	int id = *(int *) arg;
        while (1) {
		pthread_mutex_lock(&mutex); 
		while (Count == 0) pthread_cond_wait(&not_empty, &mutex); // wait and release mutex 
		printf("Consumer %d: Took %d from the buffer \n", id, Buf[Out]);
		Out = (Out + 1) % BUF_SIZE;
		Count--;
		pthread_cond_signal(&not_full);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}	
}

int main (int argc, char* argv[]) {
	
	int a[2] = {10, 100};
	int i; 
		
	pthread_t th_prd[2], th_csm[2]; 

	for (i = 0; i < 2; i++){
		pthread_create (&th_prd[i], NULL, producer, &a[i]);
		pthread_create (&th_csm[i], NULL, consumer, &a[i]);
	}

	for (i = 0; i < 2; i++) {
		pthread_join (th_prd[i], NULL); 
		pthread_join (th_csm[i], NULL);
	}


	return 0; 
}
