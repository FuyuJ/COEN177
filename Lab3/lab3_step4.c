/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab3 - Inter-process Communication - Pipes
 * Description: This program implements the shell command: 
 * 		cat /etc/passwd | grep root by passing half of
 * 		the command from one end of the pipe to the other
 * 		end. It makes use of execlp to run the command. 
 */
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
		dup2(fds[1], 1);
		close(fds[0]);
		execlp("cat", "cat", "/etc/passwd", NULL);
	}
	/*child 2 duplicates upstream into stdout */
	else if (fork() == 0) {
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("grep", "grep", "root", NULL);
	}
	/*parent closes both ends and wait for children */
	else {
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
}
