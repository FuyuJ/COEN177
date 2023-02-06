/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab5 - Synchronization using semaphores, lock, and condition variables
 * Description: This program creates 10 threads where each thread is synchronized via
 * 		a mutex lock. Each thread rpints out a statement when they are entering
 * 		the critical section and when they have returned.
 */


 // Thread Sychronization

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t m; 

void* go(void* arg) { 
  	//lock the mutex
	pthread_mutex_lock(&m); //entry section
  	printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
   	sleep(1); 
  	//unlock the mutex
	pthread_mutex_unlock(&m); //exit section 
  return (NULL);
} 

int main() {
	//create mutex 
	pthread_mutex_init(&m, NULL);
	static int i;
	//Create 10 threads to execute function go() while passing i
	for (i = 0; i < NTHREADS; i++)  
   		pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
	//main waits for threads to complete execution
	for (i = 0; i < NTHREADS; i++) {
   		pthread_join(threads[i],NULL);
   		printf("\t\t\tThread %d returned \n", i);
   	}
	printf("Main thread done.\n");
	//destroy mutex
	pthread_mutex_destroy(&m); 
	return 0; 
} 
