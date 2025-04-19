#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <pthread.h>
#include <semaphore.h>

#define BUF_SIZE 5 
int Buf[BUF_SIZE]; 
int Count; 
int In, Out; 

// Semaphore implementation 
// sem_wait (&s); Decrement and wait if < 0 
// sem_post (&s); Increment s 

sem_t empty; 
sem_t full; 
sem_t mutex; 

void* producer (void *arg) { // 'N' producer
	int id = *(int *) arg; 

	while (1) {
		int x = rand() % 10; // a random number produced 
		// mutex using sem_t 
		sem_wait (&empty); 
		sem_wait (&mutex);
		Buf[(++In) % BUF_SIZE] = x;
		Count++;
		printf("Producer %d: Added item %d to the buffer \n", id, x);
		sem_post(&mutex);
		sem_post(&full);
		sleep(1);
	}
}

void* consumer (void *arg) {
	int id = *(int *) arg;
        while (1) {
		sem_wait(&full);
		sem_wait(&mutex);
		printf("Consumer %d: Took %d from the buffer \n", id, Buf[Out]);
		Out = (Out + 1) % BUF_SIZE;
		Count--;
		sem_post(&mutex);
		sem_post(&empty);
		sleep(1);
	}	
}

int main (int argc, char* argv[]) {
	
	int a[2] = {10, 100};
	int i; 
	
	sem_init (&mutex, 0, 1);   
	sem_init (&empty, 0, BUF_SIZE); 
	sem_init (&full, 0, 0);

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
