#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <sys/types.h> 
#include <sys/times.h> 

extern long times();

void Child (int num) {
	int i; 
	struct tms x, y;
	long t1, t2; 

	t1 = times (&x); 
	
	int t = 0;
	for (i = 0; i < 100000000; i++) {
		t += (t + 4) / 2;
	}	

	t2 = times (&y); 

printf("child %d: real %u user %u sys %u \n", num, t2 - t1, y.tms_utime - x.tms_utime, y.tms_stime - x.tms_stime);
	exit(0);
} 

int main (int argc, char* argv[]) {
	
	int i; 
	struct tms x, y; 

	long t1, t2; 

	t1 = times (&x); 

	for (i = 0; i < 10; i++) {
		if (fork() == 0) {
			Child(i);
		}
	}

	for (i = 0; i < 10; i++) wait((int *) 0);

	t2 = times (&y); 
	
printf("parent real %u user %u sys %u cldrn_user %u cldrn_sys %u", t2 - t1, y.tms_utime - x.tms_utime, 
		y.tms_stime - x.tms_stime, y.tms_cutime - x.tms_cutime, y.tms_cstime - x.tms_cstime);

	return 0; 
}
