#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


void allocate_matrix(int *** matrix, int length)
{
	int i;
	
	* matrix = malloc(length * sizeof(int *));

	for (i = 0x0; i < length; i++)
		(* matrix)[i] = malloc(length * sizeof(int));
}

void fill_matrix(int ** matrix, int length, int seed)
{
	int i;
	int j;

	srand(seed);

	for (i = 0x0; i < length; i++)
		for (j = 0x0; j < length; j++)
			matrix[i][j] = rand() % 3;
}

void show_matrix(int ** matrix, int length)
{
	int i;
	int j;

	for (i = 0x0; i < length; i++)
	{
		for (j = 0x0; j < length; j++)
			printf("[%d]", matrix[i][j]);
		puts("");
	}
}


void multiplication_by_rows( int ** matrix_A, int ** matrix_B, int ** matric_C,
																	int length)
{
	int i;
	int j;
	int k;

	for (i = 0x0; i < length; i++)
	{
		for (j = 0x0; j < length; j++)
			for (k = 0x0; k < length; k++)
				matric_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
	}
}


void multiplication_by_columns( int ** matrix_A, int ** matrix_B, int ** matric_C,
		                                                              int length)
{
	int i;
	int j;
	int k;

	for (i = 0x0; i < length; i++)
	{
		printf("Lenght [%d] current iteration [%d]\n", length, i);
		for (j = 0x0; j < length; j++)
			for (k = 0x0; k < length; k++)
				matric_C[i][j] += matrix_A[k][j] * matrix_B[i][k];
	}
}
  

int main(int argc, char ** argv)
{
	int ** matrix_A;
	int ** matrix_B;
	int ** matrix_C;

  	struct timeval start;
  	struct timeval stop;

	const int length = strtol(argv[0x1], NULL, 0xa);

	allocate_matrix(& matrix_A, length);
	allocate_matrix(& matrix_B, length);
	allocate_matrix(& matrix_C, length);

	fill_matrix(matrix_A, length, 1337);
	fill_matrix(matrix_B, length, 1000);

	gettimeofday(&start, 0x0);
	multiplication_by_rows(matrix_A, matrix_B, matrix_C, length);
	gettimeofday(&stop, 0x0);


	fprintf(stdout, "> Execution time\t %2.7f\n", (double) (stop.tv_usec - start.tv_usec) /
							     			1000000 + (double)(stop.tv_sec - start.tv_sec));

  return 0x0;
}
