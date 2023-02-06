/**************************
*       COEN177: Threads  *
**************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 2
pthread_t threads[NTHREADS];
int main() {
    int i;
    char *messages[] = {"Message 1: Welcome to COEN177", "Message 2: Today's lecture is on threads"};
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *) messages[i]);
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
    }
    return 0;
}
void *go(void *arg) {
 char *message;
 message = (char *) arg;
 printf("Thread %d has %s \n",  (int)pthread_self(), message);
 return 0;
}


