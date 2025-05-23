#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <sys/msg.h> 
#include <sys/ipc.h> 
#include <sys/types.h> 

#define MSGKEY 75 

struct msgform {
	long mtype; 
	char mtext[256]; 
};

int main (int argc, char* argv[]) {
	
	struct msgform msg;
	int msgid, pid, *pint; 
	
	msgid = msgget (MSGKEY, 0777); 
	pid = getpid(); 
	pint = (int *) msg.mtext; 
	*pint = pid; 
	msg.mtype = 1; 

	msgsnd(msgid, &msg, sizeof(int), 0);
	//msgrcv(msgid, &msg, 256, pid, 0); 
	printf("client: receive from pid %d\n", *pint);

	return 0; 
}
