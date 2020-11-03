#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



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

	/* srand(1337); */

	for (i = 0x0; i < rows; i++)
	{
		for (j = 0x0; j < columns; j++)
		{
			matrix[i][j] = j;

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


int thread_count;

void * hello(void * rank);

int main(int argc, char ** argv)
{

  long thread;
  pthread_t * thread_handles;
  thread_count = strtol(argv[0x1], NULL, 0xa);

  thread_handles =  malloc(thread_count * sizeof(pthread_t));

  for (thread = 0x0; thread < thread_count; thread++)
    pthread_create(& thread_handles[thread], NULL, hello,
                                        (void *) thread);


  for (thread = 0x0; thread < thread_count; thread++)
    pthread_join(thread_handles[thread], NULL);

  free(thread_handles);

  return 0x0;
}


void * hello(void * rank)
{
  long current_rank = (long) rank;

  printf("Hello from thread %ld of %d\n", current_rank, thread_count);

  return NULL;
}
