/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab4 - Developing multi-threading applications
 * Description: This program multiplies two matrices, matrixA and matrixB, and puts the
 * 		result in matrixC. It creates a thread for each row by column multiplication
 * 		for a total of N*M threads.
 */
// Lab4 - skeleton for step 3
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//values of N,M, and L 
#define N 4 
#define M 4
#define L 4

pthread_t threads[N*M];

//A, B, C matrices
double matrixA[N][M], matrixB[M][L], matrixC[N][L];
struct d {
	int i;
	int j;
};

//function prototypes
void initializeMatrix(int r,int c, double matrix[r][c]);
void *multiplyRow(void *arg);
void printMatrix(int r,int c, double matrix[r][c]);

int main(){

	int i;
	int j;
	
	
	initializeMatrix(N, M, matrixA); //initialize matrixA with random values
	initializeMatrix(M, L, matrixB); //initialize matrixB with random values

	//create N*M threads, each multiplying row A by column B to produce row of C
	//your code
        for(i = 0; i< N; i++) { 

		for (j = 0; j < M; j++) {
			
			struct d data = {.i = i, .j = j};
			//allocated the structure of data to p so that it doesn't change
			//the original pointer since we can't pass the structure by value
			//to pthread_create, only by pointer.
			struct d *p = malloc(sizeof *p);
			*p = data;
			printf("Creating thread for row: %d of matrixA and column: %d of matrixB \n", i, j);
			pthread_create(&threads[i+j], NULL, multiplyRow, p);
		}	
	}	 

	//Main thread waits for child threads to complete
	for(i=0;i<N;i++){
		pthread_join(threads[i],NULL);
	}

	//Print Matrix A, B, and C
	//your code
	//Print Matrix A
	printf("Printing Matrix A:\n");
	printf("\n");
	printMatrix(N, M, matrixA);
	printf("\n");
	//Print Matrix B
	printf("Printing Matrix B:\n");
	printf("\n");
	printMatrix(M, L, matrixB);
	printf("\n");
	//Print Matrix C
	printf("Printing Matrix C:\n");	
	printf("\n");
	printMatrix(N, L, matrixC);
	return 0;
}

//Initialize matrixA and matrixB with random values
void initializeMatrix(int r,int c, double matrixX[r][c]){
	srand(time(NULL));
	//your code
	int i, j;
	for(i = 0; i < r; i++){
		for(j = 0; j < c; j++) {
			matrixX[i][j] = rand() % 10;
		}
	}
	return;

}

//thread function: multiply row of A by columns of B --> row of C
void* multiplyRow(void *arg){
	//your code
	struct d *data = arg;
	int i = data -> i;
        int j = data -> j;
	int k;
	double temp = 0;
	//multiply the given row of A by the given column of B
	for(k = 0; k < N; k++) {
		temp += matrixA[i][k]*matrixB[k][j];
	}
	matrixC[i][j] = temp;
	//exit thread when execution is complete
	pthread_exit(0);   	
}

//Print matrices
void printMatrix(int r,int c, double matrix[r][c]){
	int i, j;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++)
			printf("%lf ",matrix[i][j]);
		printf("\n");
	}
}
