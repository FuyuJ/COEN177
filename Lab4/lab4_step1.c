/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab4- Developing multi-threaded applications
 * Description: This program creates 20 threads and prints out a
 * 		statement accompanied by the thread ID. It will then
 * 		wait for each thread to return and print it out before
 * 		exiting the program.
 */
/**************************************************************
*	threadHello.c - simple multi-threaded program.            *
*   compile with: >gcc -lp threadHello.c -o threadHello       *                                              *
**************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 20

void *go(void *);
pthread_t threads[NTHREADS];

int main() {
    static int i;
    for (i = 0; i < NTHREADS; i++)	  
       pthread_create(&threads[i], NULL, go, &i);
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
	    printf("Thread %d returned \n", i);
    }
    printf("Main thread done.\n");
}
void *go(void *arg) {
    printf("Hello from thread %d with thread ID %d \n", *(int *)arg, (int)pthread_self());
    return (NULL);
}

