/***
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: 10/01/2021 (Thursday 5-8PM)
 * Title: Lab2 - Programming in C and use of System Calls
 * Description: This program creates a parent and child. The Child
 * 		process will run the "ls" command and the Parent
 * 		process will wait until the child process terminates
 * 		before it exits.
 * ***/

#include <stdio.h>	/* printf, stderr */
#include <sys/types.h>	/* pid t */
#include <unistd.h>	/* fork */
#include <stdlib.h>	/* atoi */
#include <errno.h>	/* errno */


int main() {
	pid_t pid;
	printf("\n Before forking.\n");
	pid = fork();
	//if it fails to fork, prints out an error message
	if (pid < 0) {
		fprintf(stderr, "can't fork, error %d\n", errno);
	}
	//if it is the child process, will run the "ls" command
	if (pid == 0) {
		// Child Process
		execlp("/bin/ls", "ls", NULL);
	}
	//otherwise, the parent process will wait for child and exit
	else {
		//Parent Process
		wait(NULL);
		printf("Child Complete\n");
		exit(0);
	}
	return 0;
}
