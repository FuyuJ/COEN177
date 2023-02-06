/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab8 - Memory Management
 * Description: Implementation of Second Chance Algorithm
 */
//Lab 8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {//to 
    int pageno;
    bool bit;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int placeInArray = 0;
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
	cache[i].bit = 0;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
	//check if page is already in array, if yes, switch bit to 1
	bool foundInCache = false;
	for (i = 0; i < C_SIZE; i++) {
		if(cache[i].pageno == page_num) {
			foundInCache = true;
			cache[i].bit = 1;
			break;
		}
	}
	//if page is not in array, increment faults
	if (foundInCache == false) {
		++totalFaults;
		//until a page with bit = 0 is found, set all bits to 0
		while (cache[placeInArray].bit == 1) {
			cache[placeInArray].bit = 0;
			if (placeInArray == C_SIZE - 1) {
				placeInArray = 0;
			}
			else { 
				++placeInArray;}
		}
		//replace page with bit = 0 and increment placeInArray accordingly
		cache[placeInArray].pageno = page_num;
		if (placeInArray == C_SIZE - 1) {
			placeInArray = 0;
		} else {
			placeInArray++;
		}
	}
		
    }

    printf("%d Total Page Faults", totalFaults);
    return 0;



}
