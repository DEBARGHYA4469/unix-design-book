#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <sys/types.h> 

int main (int argc, char* argv[]) {

	int fd; 
	char buf[1024]; 
	struct stat s; 
	
	if (argc != 2) exit(0); 
	fd = open (argv[1], O_RDONLY);
	
	if (fd == -1) 
		exit(0);
	if (unlink(argv[1]) == -1)
		exit(0);
	
	if (stat(argv[1], &s) == -1)
		printf("stat %s fails as it should \n", argv[1]); 
	else 
		printf("stat %s succeeded \n", argv[1]);


	if (fstat(fd, &s) == -1) 
		printf("fstat %s fails !", argv[1]);
	else 
		printf("fstat succeeds as it should %s \n", argv[1]);

	while (read(fd, buf, sizeof(buf)) > 0) printf("%1024s", buf);
	
	return 0; 
}
