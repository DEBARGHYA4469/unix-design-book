#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <sys/wait.h> 
#include <errno.h> 
#include <sys/ptrace.h> 
#include <sys/user.h> 

int main (int argc, char* argv[]) {
	
	pid_t pid = fork(); 
	if (pid == 0) {
		ptrace (PTRACE_TRACEME, 0, NULL, NULL); 
		execl("./traced", "traced", (char *)NULL); 
		perror("execl failed");
		exit(1);
	}
	int status;
	waitpid(pid, &status, 0); 
	
	struct user_regs_struct regs; 
       	ptrace (PTRACE_GETREGS, pid, NULL, &regs);

	long addr = 0x0; 
	printf("Changing value of secret to 999");
	ptrace (PTRACE_POKETEXT, pid, (void*)addr, (long)2);
	ptrace (PTRACE_CONT, pid, NULL, NULL);
	waitpid(pid, &status, 0); 	
		
	return 0; 
}
