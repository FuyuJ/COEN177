/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab 9 - File Performance Measurement
 * Description: This program opens a file and reads it into a buffer of size
 * 		10000. The name of the file it opens is taken from the command
 * 		line "argv[1]". Using the step2.sh file, data regarding the
 * 		time performance of each file will be collected. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	//initialize buffer with size 10000
	char buffer[10000];
	//declare file 
	FILE *fp;
	//open txt file to read, gets filename from command line
	fp = fopen(argv[1], "rb");
	//reads through the whole file
	while(fread(buffer, sizeof(buffer), 1, fp)) {
	}
	//close file
	fclose(fp);
}
