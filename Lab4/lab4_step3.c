/*
 * Name: Marianne Fuyu Yamazaki Dorr
 * Date: Thursday 5PM - 8PM
 * Title: Lab 4 - Developing multi-threaded applications
 * Description: This program computes the multiplication of two matrices using threads. 
 * 		It is computed by taking the dot product of the ith row of A and the jth column of B
 * 		In this case, each thread will take one row of Matrix A and compute the multiplication
 * 		with all columns of Matrix B and then place that result in each respective row of 
 * 		Matrix C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//values of N,M, and L 
#define N 4  
#define M 4
#define L 4 

pthread_t threads[N];

//A, B, C matrices
double matrixA[N][M], matrixB[M][L], matrixC[N][L];

//function prototypes
void initializeMatrix(int r,int c, double matrix[r][c]);
void *multiplyRow(void *);
void printMatrix(int r,int c, double matrix[r][c]);

int main(){

	int i;
	int argv[N];
	initializeMatrix(N, M, matrixA); //initialize matrixA with random values
	initializeMatrix(M, L, matrixB); //initialize matrixB with random values
	//create N threads, each multiplying row A by all columns of B to produce row of C
        for(i = 0; i< N; i++) {
	//place the value of i into an array so that it won't get changed when threads swap
	argv[i] = i;
		pthread_create(&threads[i], NULL, multiplyRow, &argv[i]);	
	} 
	//Main thread waits for child threads to complete
	for(i=0;i<N;i++){
		pthread_join(threads[i],NULL);
	}

	//Print Matrix A, B, and C

	//Print Matrix A
	printf("Printing Matrix A: %d rows and %d columns\n", N, M);
	printf("\n");
	printMatrix(N, M, matrixA);
	printf("\n");
	//Print Matrix B
	printf("Printing Matrix B: %d rows and %d columns\n", M, L);
	printf("\n");
	printMatrix(M, L, matrixB);
	printf("\n");
	//Print Matrix C
	printf("Printing Matrix C: %d rows and %d columns\n", N, L);	
	printf("\n");
	printMatrix(N, L, matrixC);
	return 0;
}

//Initialize matrixA and matrixB with random values
void initializeMatrix(int r,int c, double matrixX[r][c]){
	srand(time(NULL));
	//go through each row then each column, to initialize a random value into each cell
	//using 2 nested for loops
	int i, j;
	for(i = 0; i < r; i++){
		for (j = 0; j < c; j++){
			matrixX[i][j] = rand() % 10;
		}
	}
	return;

}

//thread function: multiply row of A by columns of B --> row of C
void* multiplyRow(void *arg){
	//for each row of matrixB, go through each column and multiply by passed row of matrixA
	//using two nested for loops
	int j, k;
	for (j = 0; j < L; j++) {
		double temp = 0;
		for (k = 0; k < M; k++) {
			temp += matrixA[*(int *)arg][k] * matrixB[k][j];
		}
	matrixC[*(int *)arg][j] = temp;
	}
    return;
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
