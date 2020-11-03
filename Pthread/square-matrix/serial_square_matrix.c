#include <stdio.h>
#include <stdlib.h>


void allocate_matrix(int *** matrix, int rows, int columns)
{
	int i;

	* matrix = malloc(rows * sizeof(int *));

	for (i = 0x0; i < columns; i++)
		(* matrix)[i] = malloc(columns * sizeof(int));
}

void fill_matrix(int ** matrix, int rows, int columns)
{
	int i;
	int j;

	srand(1337);

	for (i = 0x0; i < rows; i++)
	{
		for (j = 0x0; j < columns; j++)
		{
			matrix[i][j] = rand()%100;

		}
	}
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
  

int main(int argc, char ** argv)
{

	int ** matrix;
	int rows = strtol(argv[0x1], NULL, 0xa);
	int columns = strtol(argv[0x2], NULL, 0xa);

	printf("rows[%d]\ncolumns[%d]\n", rows, columns);

	allocate_matrix(& matrix, rows, columns);

	fill_matrix(matrix, rows, columns);

	show_matrix(matrix, rows, columns);

  return 0x0;
}
