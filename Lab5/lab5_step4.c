/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab5 - Synchronization using semaphores, lock, and condition variables
 * Description: This program solves the producer-consumer problem using semaphores.
 */

// Producer - Consumer with semaphores

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#define BUFSIZE 10
#define NP 3 
#define NC 2

pthread_t tidP[NP], tidC[NC];   
int buff[BUFSIZE];
sem_t *mutex, *full, *empty; 
int p, c, in, out; 

void *producer(void *arg) {
    int item;
    int p = (int)arg;
    srand(time(0));
    do {
        item = (rand() % 100);  // random number for producer
        //wait on empty and mutex, once >0, decrement each by one and proceed
	sem_wait(empty);
        sem_wait(mutex);
       //add item to buffer and increment in index
	buff[in] = item;
	in = (in +1)%BUFSIZE; 	
	printf ("Producer #: %d produced item: %d at buffer space: %d\n", p, item, in);
        sleep(5);
        //increment mutex and full
        sem_post(mutex);
        sem_post(full);
    } while (1);
    pthread_exit(0);
}

void *consumer(void *arg) {
    int item;
    int c = (int)arg;
    srand(time(0));
    do {
	//wait on full and mutex, once > 0, decrement each by one and proceed
        sem_wait(full);
        sem_wait(mutex);
        //remove next item from buffer and increment out index
	item = buff[out];
	out= (out+1)%BUFSIZE;
        printf ("\t\t\tConsumer #: %d consumed item: %d at buffer space: %d\n", c, item, out);
        sleep(10);	
        //increment mutex and empty
	sem_post(mutex);
        sem_post(empty);
    } while (1);
    pthread_exit(0);
}

void cleanup(int sigtype){
    //destroy semaphores before terminating
    sem_unlink("empty");
    sem_unlink("full");;
    sem_unlink("mutex");

    printf("\n Terminating\n");
    exit(0);
}

int main () {
    sem_unlink("empty");
    sem_unlink("full");;
    sem_unlink("mutex");

    signal(SIGINT,cleanup); 
    //create mutex, empty, and full semaphores
    empty = sem_open("empty", O_CREAT, 0644, BUFSIZE);
    fprintf(stdout,"empty: %d\n",empty);
    full = sem_open("full", O_CREAT, 0644, 0);
    fprintf(stdout,"full: %d\n",full);
    mutex = sem_open("mutex", O_CREAT, 0644, 1); 
    fprintf(stdout,"mutex: %d\n",mutex);  
    //Create Producer threads
    for (p = 0; p < NP; p++)
        pthread_create (&tidP[p], NULL, producer, (void*)(size_t)p);
    //Create Consumer threads
    for (c = 0; c < NC; c++)
        pthread_create (&tidC[c], NULL, consumer, (void*)(size_t)c);
   // main thread waiting for consumer and producer threads to complete their tasks
    
    //main waits for Producer threads
    for (p = 0; p < NP; p++) {
        pthread_join(tidP[p], NULL);
        printf("Producer thread %d returned\n", p);
    }
   //main waits for Consumer threads
    for (c = 0; c < NC; c++) {
        pthread_join(tidC[c], NULL);
        printf("\t\t\tConsumer thread %d returned\n", c);
    }
    printf("Main thread finished\n");
    //destroy semaphores
    sem_unlink("empty");
    sem_unlink("full");;
    sem_unlink("mutex");
    return 0;
}
