/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab 9 - File Performance Measurement
 * Description: This program opens a file and reads it into a buffer whose size
 * 		is taken from the command line "argv[2]". The name of the file it
 * 		opens is taken from the command line "argv[1]". Using the step3.sh file, 
 * 		data regarding the time performance of each file with different buffer 
 * 		sizes will be collected. 	
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	//initialize buffer with 2nd command line arg
	char buffer[atoi(argv[2])];
	//declare file
	FILE *fp;
	//open txt file to read, gets filename from 1st command line arg
	fp = fopen(argv[1], "rb");
	//reads through whole file
	while(fread(buffer, sizeof(buffer), 1, fp)) {
	}
	//close file
	fclose(fp);
}
