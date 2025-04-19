#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <signal.h> 

int Buf[4096];
char* func_map[4096];

void handler (); 

int main (int argc, char* argv[]) {
	
	extern void f(); 
	extern void g(); 

	unsigned long long offset, end_addr, scale, f_addr, g_addr, text; 
	signal (SIGINT, handler); 
	
	end_addr = (long long) (&handler);
	offset = (long long) (&main); 

	text = (end_addr - offset + sizeof(int) - 1) / sizeof(int); 
	scale = 0xffff; 	
	
	printf("offset %li end_addr %li, text %li \n", offset, end_addr, text); 

	f_addr = (long long ) (&f); 
	g_addr = (long long) (&g); 
	
	printf("Size-of-buf %d, f-addr-offset %li , g-addr-offset %li \n", (sizeof(int) * text) ,f_addr - offset, g_addr - offset);

	profil(Buf, sizeof(int) * text, offset, scale); 

	for (;;){
		f();
		g();
	}

	return 0; 
}

void f() { int x = 3; x = x + 2; } 
void g() { int y = 4; y = y + 3; }

void handler() {
	int i;
	for (i = 0; i < 4096; i++) {
		if (Buf[i]) 
			printf("Buf[%d] = %d\n", i, Buf[i]);
	}
	exit(0);
}
