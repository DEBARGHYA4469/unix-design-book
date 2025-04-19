#include <stdio.h> 
#include <unistd.h> 
#include <termios.h> 

char getch(){
	struct termios oldt, newt; 
	char c; 
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt; 
	newt.c_lflag &= ~(ICANON | ECHO); // disable canonical mode and echo 
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	read(STDIN_FILENO, &c, 1);

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return c;
}

int main () {
	printf("Press any key (q to quit): \n"); 
	char c; 
	while ((c=getch()) != 'q') {
		printf("You pressed: %c \n", c);
	}
	return 0;
}
