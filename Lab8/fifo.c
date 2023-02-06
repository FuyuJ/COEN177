/*
* Name: Marianne Fuyu Yamazaki Dorr
* Date: Thursday 5PM - 8PM
* Title: Lab8 - Memory Management
* Description: Implementation of FIFO Algorithm
*/

//Lab 8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct { 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int numReq = 0;
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }
    int placeInArray = 0;
    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
	++numReq;
	bool foundInCache = false;
	for (i = 0; i < C_SIZE; i++) {
		if(cache[i].pageno == page_num){
			//page is already in memory so no page faults
			foundInCache = true;
			break;
		}
	}
	if(foundInCache == false){ 
		//page not found, so increase number of faults
		++totalFaults;
		//place new page at location given by placeInArray
		cache[placeInArray].pageno = page_num;
		//reset placeInArray to 0 if at end of array, else increment by 1
		if(placeInArray == C_SIZE - 1) {
			placeInArray = 0;
		} else {
			placeInArray++;
		}
	}
		
    }
    printf("%d Total Page Faults \n", totalFaults);
    printf("numRequests: %d \n", numReq);
    return 0;



}
