//Thread Synchronization - Semaphores
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>


#define NTHREADS 10

void *go(void *arg);
//void cleanup(int sigtype);

pthread_t threads[NTHREADS];
sem_t *mutex;

int main() {
    //signal(SIGINT,cleanup);
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) 
        pthread_join(threads[i],NULL);
    sem_unlink("mutex");
    return 0;
}

void *go(void *arg) {
    printf("Thread %d is now attempting ....\n",  (int)arg);
    sem_wait(mutex);
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n",  (int)arg);
    sem_post(mutex);
    pthread_exit(0);
}

/*void cleanup(int sigtype){
    sem_unlink("mutex");
    printf("\n Terminating\n");
    exit(0);
}*/