/***
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: 10/01/2021 (Thursday 5-8PM)
 * Title: Lab2 - Programming in C and use of System Calls
 * Description: This program creates two threads and each thread
 * 		will print out a statement 100 times incrementing
 * 		every time.
 * ***/
#include <stdio.h>	/* printf, stderr */
#include <sys/types.h>	/* pid t */
#include <unistd.h>	/* fork */
#include <stdlib.h>	/* atoi */
#include <errno.h>	/* errno */
#include <pthread.h>   /*pthread_create */

// printhundred() prints a statement 100 times and it
// is executed as a thread when its name is specified
// in pthread_create()
void *printhundred(void *varg){
	int i;
	for (i = 0; i < 100; i++) {
		printf("Thread process %d\n", i);
	}
        return;
}

//define immutable variables
#define NTHREADS 2
pthread_t threads[NTHREADS]; 
                                       
int main() {
	printf("Before Thread\n");
	int i;
	//creates two threads that receive the printhundred() function as arg
	for (i = 0; i < NTHREADS; i++) 
		pthread_create(&threads[i], NULL, printhundred, NULL);
	//threads wait for the other thread to end
	for (i = 0; i < NTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	printf("After Thread\n");	
	exit(0);
}
