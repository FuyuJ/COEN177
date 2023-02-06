/***
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5-8PM
 * Title: Lab2 - Programming in C and use of Systems Calls
 * Description: This program creates a total of seven processes with each 
 * 		parent process having exactly two children. It will print
 * 		out the id of the child and parent after each successful 
 * 		fork. 
 * ***/
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
 
int main() {
	printf("before forking.\n");
	//forks into Parent and Child1, proceeds into if statement if it is Parent
	if (fork() == 0) {
		//P1 creates P2
		printf("Child id %d from parent pid %d\n", getpid(), getppid());
		wait(NULL);
		//forks into Parent and Child, proceeds if it is Parent(aka Child1)
		if (fork() == 0) {
			//P2 creates P4
			printf("Child id %d from parent pid %d\n", getpid(), getppid());
			wait(NULL);
		} else if (fork() == 0) {
			//P2 creates P5
			printf("Child id %d from parent pid %d\n", getpid(), getppid());
			wait(NULL);
		}
	} else if (fork() == 0) {
		//P1 creates P3 
		printf("Child id %d from parent pid %d\n", getpid(), getppid());
		wait(NULL);
		if (fork() == 0) {
			//P3 creates P6
			printf("Child id %d from parent pid %d\n", getpid(), getppid());
			wait(NULL);
		} else if(fork()==0) {
			//P3 creates P7
			printf("Child id %d from parent pid %d\n", getpid(), getppid());
			wait(NULL);
		}						
	}
	wait(NULL);
}
