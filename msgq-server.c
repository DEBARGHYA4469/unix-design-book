#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>

#define MSGKEY 75 

struct msgform {
	long mtype;
	char mtext[256];
} msg;

int msgid; 

int main (int argc, char* argv[]) {
	
	int i, pid, *pint; 
	extern void cleanup(); 

	for (i = 0; i < 20; ++i) signal(i, cleanup);
	
	msgid = msgget (MSGKEY, 0777 | IPC_CREAT);

	for (;;){
		msgrcv(msgid, &msg, 256, 1, 0);
		pint = (int *) msg.mtext;
		pid = *pint;
		printf("server: receive from pid %d\n", pid);
		msg.mtype = pid; 
		*pint = getpid();
		msgsnd(msgid, &msg, sizeof(int), 0);
	}

	return 0; 
}

void cleanup(){
	msgctl(msgid, IPC_RMID, 0);
	exit(0);
}
