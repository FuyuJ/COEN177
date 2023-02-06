/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab 9 - File Performance Measurement
 * Description: This program creates multiple copies of a txt file. Concurrent
 * 		multiple threads will each read and copy a file. The number of
 * 		threads will be set based on a value from the command line
 * 		"argv[3]". Data regarding the time performance will be collected
 * 		via the step5.sh file which will run this program for 2, 8, 32, and 64
 * 		concurrent threads where each will read/write all the different txt files
 * 		using buffers of different sizes as well (100, 1000, 10000, 100000).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

void *file_copy(void *);
char *buffer;
char *fileparam;

int main(int argc, char *argv[]) {
	int i;
	//allocate size of buffer by passing 2nd arg from command line
	buffer = malloc(atoi(argv[2]) *(sizeof buffer[0]));
	//initialize number of threads from 3rd arg from command line
	int NTHREADS = atoi(argv[3]);
	//array of integers to store i values to keep track of threads
	int argi[NTHREADS];
	//declare array of threads of size NTHREADS
	pthread_t threads[NTHREADS];
	//assign 1st arg from command line to fileparam (name of txt file to read from)
	fileparam = argv[1];
	//create threads
	for (i = 0; i < NTHREADS; i++) {
		argi[i] = i;
		pthread_create(&threads[i], NULL, file_copy, &argi[i]);
	}
	//wait for threads to return
	for (i = 0; i < NTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}
}

void *file_copy(void *arg) {
	//declare files
	FILE *fcopy;
	FILE *fp;
	//create name for copy file
	char filename[] = "copy";
	int id = *(int *)arg;
	char *fileid;
	//convert id to character and store it into fileid
	asprintf(&fileid,"%d", id); 
	//concatenate fileid to filename and append ".txt" to complete new filename
	strcat(filename, fileid);
	strcat(filename, ".txt");
	//open both files
	fp = fopen(fileparam, "rb");
	fcopy = fopen(filename, "w");

	//copy from fp file to fcopy file
	while(fread(buffer, sizeof(buffer), 1, fp)) {
		fwrite(buffer, 1, sizeof(buffer), fcopy);
	}
	//close both files
	fclose(fcopy);
	fclose(fp);

	return (NULL);
}

