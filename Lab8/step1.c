/*
* Name: Marianne Fuyu Yamazaki Dorr
* Date: Thursday 5PM - 8PM
* Title: Lab8 - Memory Management
* Description: This program generates a text file with random values limited in the range of 
* 		0 to capNumber. It creates someNumber of random values. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#define capNumber 20
#define someNumber 20
int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer [sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    for (i=0; i<someNumber; i++){
        sprintf(buffer, "%d\n", rand()%capNumber);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}

