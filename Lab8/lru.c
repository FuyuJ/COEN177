/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab8 - Memory Management
 * Description: Implementation of LRU Algorithm
 */
//Lab 8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int j; //index for shifting algorithm
   
    int placeInArray = 0;
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
 
	bool foundInCache = false;
        //keep lru at beginning of array and mru at end of array
	for(i = 0; i < C_SIZE; i++) {
                if (cache[i].pageno == page_num) {
                        
                        ref_page temp = cache[i];
                        for (j = i; j < C_SIZE - 1; j++) {
                                if (cache[j].pageno == -1) { break;}
                                 cache[j].pageno = cache[j+1].pageno; 
                        } 
                        cache[j] = temp;                                                
                        foundInCache = true;
                        break;
                }
        }
	//if not found, insert page in array
        if (foundInCache == false) {
		totalFaults++;
		//check if any empty slots
		bool isEmpty = false;
		for (i = 0; i < C_SIZE; i++) {
			if (cache[i].pageno == -1) {
				isEmpty = true;
				placeInArray = i;
				break;
			}
		}
		//if empty, place page at first empty slot
		if (isEmpty) {
			cache[placeInArray].pageno = page_num;
		//else shift all elements one to the left, thus losing data from lru page
		} else {
			for(i = 0; i < C_SIZE - 1; i++){
				cache[i].pageno = cache[i+1].pageno;
			}
			//insert new page at end of array
			cache[C_SIZE - 1].pageno = page_num;
		}
	}
    }
    printf("%d Total Page Faults", totalFaults);
    return 0;
}
