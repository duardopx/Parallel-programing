#include <stdio.h>
#include <stdlib.h>


void allocate_matrix(int *** matrix, int rows, int columns)
{
	int i;
	
	* matrix = malloc(rows * sizeof(int *));

	for (i = 0x0; i < rows; i++)
		(* matrix)[i] = malloc(columns * sizeof(int));
}

void allocate_vector(int ** vector, int vector_length)
{
	* vector = malloc(sizeof(* vector) * vector_length);
}


void fill_matrix(int ** matrix, int rows, int columns)
{
	int i;
	int j;

	srand(1337);

	for (i = 0x0; i < rows; i++)
		for (j = 0x0; j < columns; j++)
			matrix[i][j] = rand() % 0x4;
}


void fill_vector(int * vector, int vector_length)
{
	int i;
	srand(1337);

	for (i = 0x0; i < vector_length; i++)	
		vector[i] = rand() % 0x4;
}

void show_vector(int * vector, int vector_length)
{
	int i;

	for (i = 0x0; i < vector_length; i++)
		printf("[%d]", vector[i]);

	puts("");
}

void show_matrix(int ** matrix, int rows, int columns)
{
	int i;
	int j;

	for (i = 0x0; i < rows; i++)
	{
		for (j = 0x0; j < columns; j++)
			printf("[%d]", matrix[i][j]);
		puts("");
	}
}


void multiplication(int * resulting_vector, int * vector, int vector_length,
															  int ** matrix,
												     int matrix_rows_length,
												  int matrix_columns_length)
{
	int i;
	int j;
	
	for (i = 0x0; i < matrix_rows_length; i++)
		for (j = 0x0; j < matrix_columns_length; j++)
			resulting_vector[i] += matrix[i][j] * vector[j];
}
  

int main(int argc, char ** argv)
{
	int * vector;
	int ** matrix;
	int * resulting_vector;

	int rows = strtol(argv[0x1], NULL, 0xa);
	int columns = strtol(argv[0x2], NULL, 0xa);
	int vector_length = strtol(argv[0x3], NULL, 0xa);

	/* printf("> arguments %s %s %s\n", argv[1], argv[2], argv[3]); */

	allocate_matrix(& matrix, rows, columns);
	allocate_vector(& vector, vector_length);
	allocate_vector(& resulting_vector, vector_length);

	fill_matrix(matrix, rows, columns);
	fill_vector(vector, vector_length);

	multiplication(resulting_vector, vector, vector_length, matrix, rows, columns);

	puts("[>] Matrix");
	show_matrix(matrix, rows, columns);

	puts("[>] Vector");
	show_vector(vector, vector_length);


	puts("[>] Resulting vector");
	show_vector(resulting_vector, vector_length);

  return 0x0;
}
