/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab5 - Synchronization using semaphores, lock, and condition variables
 * Description: This program solves the producer-consumer problem using condition
 * 		variables.
 */
// Producer - Consumer with condition variable

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>

#define BUFSIZE 10
#define NP 3 
#define NC 2

pthread_t tidP[NP], tidC[NC];   
int buff[BUFSIZE];
pthread_mutex_t mutex;
pthread_cond_t full, empty; 
int p, c, in, out, count; 

void *producer(void *arg) {
    int item;
    int p = (int)arg;
    srand(time(0));
    do {
        item = (rand() % 100);  // random number for producer
        //lock the mutex
	pthread_mutex_lock(&mutex);
        //while count is equal to BUFSIZE, wait for consumer to remove items
	while(count == BUFSIZE)
		pthread_cond_wait(&empty, &mutex);
        //add item to buffer and increment in index
        buff[in] = item;
	in = (in+1)%BUFSIZE;
	printf ("Producer #: %d produced item: %d at buffer space: %d\n", p, item, in);
        //after producing an item, increment conut by 1
        count++;
	//signal full and unlock mutex
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    } while (1);
    pthread_exit(0);
}

void *consumer(void *arg) {
    int item;
    int c = (int)arg;
    srand(time(0));
    do {
	//lock the mutex
        pthread_mutex_lock(&mutex);
	//if count is 0, loop until producer adds items
        while (count == 0)
	    pthread_cond_wait(&full, &mutex);
        //remove next item from buffer and increment out index
        item = buff[out];
	out = (out+1)%BUFSIZE;
	printf ("\t\t\tConsumer #: %d consumed item: %d at buffer space: %d\n", c, item, out);
	//after consuming item, reduce count by 1
        count--;
	//signal empty and unlock mutex	
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        sleep(12);
    } while (1);
    pthread_exit(0);
}

int main () {
    //create mutex lock and empty and full condition variables 
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);
    //create the Producer threads
    for (p = 0; p < NP; p++)
        pthread_create (&tidP[p], NULL, producer, (void *)(size_t)p);
    //create the Consumer threads
    for (c = 0; c < NC; c++)
        pthread_create (&tidC[c], NULL, consumer, (void *)(size_t)c);
    // main thread waiting for consumer and producer threads to complete their tasks
    
    //main waits for producer threads
    for (p = 0; p < NP; p++) {
        pthread_join(tidP[p], NULL);
        printf("Producer thread %d returned\n", p);
    }
    //main waits for consumer threads
    for (c = 0; c < NC; c++) {
        pthread_join(tidC[c], NULL);
        printf("\t\t\tConsumer thread %d returned\n", c);
    }
    printf("Main thread finished\n");
    //destroy mutex lock and empty and full condition variables
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&empty);
    pthread_mutex_destroy(&full);
	return 0;
}

