/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab3 - Inter-process Communication - Pipes
 * Description: This program implements the producer-consumer message communication
 * 		using pipes. The Producer will ask the user to input a sentence of 
 * 		at most 20 characters and store that into the character array message.
 * 		It will then pass that message into the pipe where the Consumer will
 * 		pick up the message, store it into the character array str and then
 * 		print it out. 
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h> 
//main
int main() {
	int fds[2];
	pipe(fds);
	char message[20];
	int i;
	int count;
	char str[20];
	/*child 1 duplicates downstream into stdin */
	if (fork() == 0) {
		close(fds[0]);
		printf("Producer: Please input a sentence (at most 20 characters)\n");
		fgets(message, sizeof(message), stdin);
		printf("\n");
		write(fds[1], message, strlen(message) + 1);
	}
	/*child 2 duplicates upstream into stdout */
	else if (fork() == 0) {
		close(fds[1]);
		printf("Consumer: ");
		usleep(1); 
		read(fds[0], str, 20);
		printf(str);
		printf("\n");
		exit(0);
	}
	else { /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
return 0;
}
		
