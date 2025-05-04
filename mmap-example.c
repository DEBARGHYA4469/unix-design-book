#include <stdio.h> 
#include <fcntl.h> 
#include <sys/mman.h> 
#include <unistd.h> 

int main () {
	
	int fd = open ("data.txt", O_RDWR);
	size_t len = 4096; 
	
	// @brief: mmap: avoids write sys call, copying from user space -> kernel space 
	// 		 data is written directly from user space to disk as per OS 
	// 		 pages which are touched are marked as dirty, later flushed to disk 
	// 		 This is particularly useful for the case, where file is big and cannot be fit into RAM. 
	 
	char* ptr = mmap (NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED) {
		perror("mmap");
		return 1;
	}
	printf("first char: %c\n", ptr[0]); 
	ptr[0] = 'X';
	munmap(ptr, len);
	close(fd);

	return 0;
}
