/***********
 * Basil Lin
 * ECE 6730
 * smallball.c
 ***********/
 
#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(int argc, char** argv) {

	clock_t begin = clock(); //begins timing

	MPI_Init(NULL, NULL); //initializes MPI environment

	int r, s;
	MPI_Comm_rank(MPI_COMM_WORLD, &r); //grabs rank
	MPI_Comm_size(MPI_COMM_WORLD, &s); //grabs size

	char p[5]; //token to pass

	if (r == 0) { //first process
		strcpy(p, "ball");
		MPI_Send(&p, 1, MPI_INT, (r + 1) % s, 0, MPI_COMM_WORLD);
		printf("Process %d sent %s to process %d\n", r, p, (r + 1) % s);
		MPI_Recv(&p, 1, MPI_INT, s - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d received %s from process %d\n", r, p, s - 1);
	} else { //other processes
		MPI_Recv(&p, 1, MPI_INT, r - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d received %s from process %d\n", r, p, r - 1);
		MPI_Send(&p, 1, MPI_INT, (r + 1) % s, 0, MPI_COMM_WORLD);
		printf("Process %d sent %s to process %d\n", r, p, (r + 1) % s);
	}	

		
	MPI_Finalize(); //closes MPI environment
	
	clock_t end = clock(); //ends timing
	double t = (double)(end - begin) / CLOCKS_PER_SEC; //calculates time
	
	printf("Process %d took %lf seconds\n", r, t); //prints time for each process
	
	return 0;
	
}

