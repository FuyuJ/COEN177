/**************************
*	pipe()
* Name: Marianne Fuyu Yamazaki Dorr
* Date: Thursday @ 5PM - 8PM
* Title: Lab3 - Inter-process Communication - Pipes
* Description: This program prints a command into the terminal using pipes 
* 	       between two child processes. It lists the files in the current
* 	       directory in alphanumerical order. I had to compile/run the 
* 	       following program and demonstrate it to the TA.  
**************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h> 
//main
int main() {
 	int fds[2];
 	pipe(fds);
	/*child 1 duplicates downstream into stdin */
	if (fork() == 0) {
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("sort", "sort", 0); 
	}
	/*child 2 duplicates upstream into stdout */
	else if (fork() == 0) {
		dup2(fds[1], 1);
		close(fds[0]);
		execlp("ls", "ls", 0); 
	}
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0); 
	}
return 0;
} 
