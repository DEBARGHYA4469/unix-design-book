#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 

int main () {
	int server_fd, client_fd; 
	struct sockaddr_in server_addr, client_addr; 
	char buf[1024] = {0}; 
	socklen_t addr_len = sizeof(client_addr); 

	// create a socket IPv4, TCP 
	server_fd = socket (AF_INET, SOCK_STREAM, 0); 
	// bind it to local host 
	server_addr.sin_family = AF_INET; 
	server_addr.sin_addr.s_addr = INADDR_ANY; // open to receive on any local interfaces, accept connections to connect to any IP addr like localhost/LO, Wi-Fi IP, Ethernet IP, any other ...  
	server_addr.sin_port = htons(8080); 
	
	bind (server_fd, (struct sockaddr *)&server_addr, sizeof (server_addr));
	
	// listen for incoming connections 
	listen (server_fd, 5); // max 5 connection queued 
	
	printf("Server listening on port 8080...\n"); 

	// accept a connection 
	client_fd = accept (server_fd, (struct sockaddr *) &client_addr, &addr_len); 
	
	// read the data from the client 
	read (client_fd, buf, sizeof(buf));
	printf("Received: %s\n", buf); 

	// send a reply 
	const char* reply = "Hello from Server!!";
	write(client_fd, reply, strlen(reply));
	
	close (client_fd);
	close (server_fd);

	return 0;
}


