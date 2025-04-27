#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 

int main () {

	int sock; 
	struct sockaddr_in server_addr; 
	char buf[1024] = {0}; 
	
	// create a sock 
	// pton : presentation to net 
	// hton : host to net 
	// ntoh : net to host 
	sock = socket (AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET; 
	server_addr.sin_port = htons(8080); 
	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
	
	// connect to server
	connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
       	
	// send a message 
	const char* msg = "Hello from client!!"; 
	write (sock, msg, strlen(msg)); 

	read (sock, buf, sizeof(buf));
	printf("Server reply: %s\n", buf);

	// close the socket 
	close (sock);	

	return 0;
} 
