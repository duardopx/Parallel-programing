#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


struct thread_args
{
    pthread_t rank; 
    int thread_rank; 
   	int thread_count; 
   	int matrix_lenght; 
    int ** matrix_A; 
    int ** matrix_B; 
    int ** matrix_C; 
} thread_args;

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
			matrix[i][j] = i+1;
	/* matrix[i][j] = rand() % 0x3; */
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


void * multiplication(void * thread_args)
{
	int i;
	int j;
	int k;

	int start;
	int end;

	struct thread_args * thread_handless = (struct thread_args *) thread_args;

	int ** Matrix_A;
	int ** Matrix_B;
	int ** Matrix_C;

	int matrix_lenght;
	int thread_rank;
	int thread_count;
	int local_matrix_length;


	Matrix_A = thread_handless->matrix_A;
	Matrix_B = thread_handless->matrix_B;
	Matrix_C = thread_handless->matrix_C;

	thread_rank = thread_handless->thread_rank;
	thread_count = thread_handless->thread_count;

	matrix_lenght = thread_handless->matrix_lenght;
	local_matrix_length = matrix_lenght / thread_count;

	start = thread_rank * local_matrix_length;
	end = start + local_matrix_length;

	for (i = start; i < end; i++)
		for (j = 0x0; j < matrix_lenght; j++)
			for (k = 0x0; k < matrix_lenght; k++)
				Matrix_C[i][j] += Matrix_A[i][k] * Matrix_B[k][j];

	return NULL;
}


int main(int argc, char ** argv)
{
	int thread;

	int ** matrix_A;
	int ** matrix_B;
	int ** matrix_C;

  	struct timeval start;
  	struct timeval stop;

	struct thread_args * thread_handless;


	int length = strtol(argv[0x1], NULL, 0xa);
	int thread_count = strtol(argv[0x2], NULL, 0xa);

	thread_handless = malloc(sizeof(struct thread_args) * thread_count);

	thread_handless->thread_count = thread_count;

	allocate_matrix(& matrix_A, length);
	allocate_matrix(& matrix_B, length);
	allocate_matrix(& matrix_C, length);

	fill_matrix(matrix_A, length, 1337);
	fill_matrix(matrix_B, length, 1000);

	gettimeofday(&start, 0x0);

	for (thread = 0x0; thread < thread_count; thread++)
	{
		thread_handless[thread].rank = thread;
		thread_handless[thread].thread_rank = thread;
		thread_handless[thread].thread_count = thread_count;
		thread_handless[thread].matrix_lenght = length;
		thread_handless[thread].matrix_A =  matrix_A;
		thread_handless[thread].matrix_B =  matrix_B;
		thread_handless[thread].matrix_C =  matrix_C;

		if (pthread_create(& thread_handless[thread].rank, NULL, multiplication, (void *) & thread_handless[thread]))
		{
			fprintf(stderr, "Error on thread creation");
			 exit(0x1);
		}
	}

	for (thread = 0x0; thread < thread_count; thread++)
		if (pthread_join(thread_handless[thread].rank, NULL))
		{
			fprintf(stderr, "Error on join threads\n");
			exit(0x1);
		}

	gettimeofday(&stop, 0x0);

	/* puts("[>] Matrix A \n--------------------"); */
	/* show_matrix(matrix_A, length); */
	
	/* puts("[>] Matrix B \n--------------------"); */
	/* show_matrix(matrix_B, length); */

	/* puts("[>] Matrix C \n--------------------"); */
	/* show_matrix(matrix_C, length); */

	fprintf(stdout, "> Execution time\t %2.7f\n", (double) (stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));

  return 0x0;
}
