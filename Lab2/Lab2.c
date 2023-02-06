/***
 * Name : Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5-8PM
 * Title: Lab2 - Programming in C and use of Systems Calls
 * Description: This program forks the process into a parent and child.
 * 		The Parent will print out a statement 100 times, incrementing
 * 		the count each time indented by three tab spaces. The Child
 * 		will also print out a statement 100 times, incrementing the count
 * 		each time but not indented at all. The program receives an 
 * 		argument from the command line to determine the time in
 * 		microseconds the program much sleep for after each print statement
 ****/
#include <stdio.h>	/* printf, stderr */
#include <sys/types.h>	/* pid t */
#include <unistd.h>	/* fork */
#include <stdlib.h>	/* atoi */
#include <errno.h>	/* errno */
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
	pid_t pid;
	int i;
	int n = atoi(argv[1]); //n microseconds to input from keyboard for delay
	//printf("%s\n", n);
	printf("\n Before forking.\n");
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "can't fork, error %d\n", errno);
	}
	if (pid > 0) {
		// Parent process
		for (i = 0; i < 100; i++) {
			printf("\t \t \t Parent Process %d \n", i);
			usleep(n);
		}
	}
	else {
		//Child Process
		for (i = 0; i < 100; i++) {
			printf("Child process %d\n", i);
			usleep(n);
		}
	}
	return 0;
}
