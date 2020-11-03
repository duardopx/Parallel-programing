#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include "mpi.h"




void swap(int * first, int * last)
{
	int tmp = * first;
	* first = * last;
	* last = tmp;
}


void odd_even_sort(int * array, int array_length)
{
    int i;
    int sorted = false;

    while (sorted == false)
    {
        sorted = true;

        for (i = 1; i < array_length - 1; i += 2)
            if (array[i] > array[i + 1])
            {
                swap(& array[i], & array[i + 0x1]);
                sorted = false;
            }

        for (i = 0x0; i < (array_length - 0x1); i += 2)
            if (array[i] > array[i + 0x1])
            {
                swap(& array[i], & array[i + 0x1]);
                sorted = 0x0;
            }
    }
}


void print_array(char * log, int * array, int length)
{
	int i;
	printf("> %s\n", log);

	printf("----------------------------------------\n");
	for (i = 0x0; i < length; i++)
		printf("[%d]", array[i]);

	puts("");
	fflush(stdout);
}


void fill_array(int * array, int length)
{
	long i;
	srand(1337);

		for (i = 0x0; i < length; i++)
			array[i] = rand() % 100;
}


void lower(int * local_array, int * nextArray, int local_array_length)
{
	int i = 0x0;
	int merge_array_length = local_array_length * 0x2;
	int * merge_array = malloc(sizeof(int) * merge_array_length);

	for (i = 0x0; i < merge_array_length; i++)
	{
		if (i < local_array_length)
		{
			merge_array[i] = local_array[i];
		}

		else
		{
			merge_array[i] = nextArray[i - local_array_length];
		}
	}

	odd_even_sort(merge_array, merge_array_length);

	for (i = 0; i < local_array_length; i++)
		local_array[i] = merge_array[i];

	free(merge_array);
}


void upper(int * local_array, int * previous_array, int local_array_length)
{
	int i;
	int j;

	int merge_array_length = local_array_length * 0x2;
	int * merge_array = malloc(sizeof(int) * merge_array_length); 

	for (i = 0x0; i < merge_array_length; i++)
	{
		if (i < local_array_length)
		{
			merge_array[i] = local_array[i];
		}

		else
		{
			merge_array[i] = previous_array[i - local_array_length];
		}
	}

	odd_even_sort(merge_array, merge_array_length);

	j = 0x0;
	for (i = local_array_length; i <= merge_array_length; i++, j++)
	{
		local_array[j] = merge_array[i];
	}

	free(merge_array);
}

void front_swap(int * local_array, int local_array_length, int rank)
{
	int * next_array = malloc(sizeof(int) * local_array_length);

	MPI_Send(local_array, local_array_length, MPI_INT, (rank + 0x1),
																0x0,
																MPI_COMM_WORLD);

	MPI_Recv(next_array, local_array_length, MPI_INT, (rank + 0x1),
																0x0,
																MPI_COMM_WORLD,
																MPI_STATUS_IGNORE);

	lower(local_array, next_array, local_array_length);
	free(next_array);
}



void back_swap(int * local_array, int local_array_length, int rank){


    odd_even_sort(local_array, local_array_length);
  

  
    MPI_Send(local_array, local_array_length, MPI_INT, (rank - 0x1),
																0x0,
    															MPI_COMM_WORLD);


  
    int *previous_array = malloc(local_array_length * sizeof(int));

    MPI_Recv(previous_array, local_array_length, MPI_INT, (rank - 0x1), 0x0,
																MPI_COMM_WORLD,
	    														MPI_STATUS_IGNORE);

    upper(local_array, previous_array, local_array_length);

    free(previous_array);
}


int main(int argc, char ** argv)
{
    int i;
    int rank;
    int comm_size;

	int array_length;
	int local_array_length;

  	struct timeval start;
  	struct timeval stop;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

	array_length = strtol(argv[0x1], NULL, 0xa);
	local_array_length = array_length / comm_size;


    int * array = malloc(array_length * sizeof(int));
    int * local_array = malloc(local_array_length * sizeof(int));


    if (rank == 0)
    { 
        fill_array(array, array_length);


        /* print_array("Main Array",array,N); */
        MPI_Scatter(array, local_array_length, MPI_INT, local_array,
													local_array_length,
        											MPI_INT,
        											0x0,
        											MPI_COMM_WORLD);
		gettimeofday(&start, 0x0);
    }

    int *displs = malloc(comm_size * sizeof(int));
    /* int i; */
    for (i = 0; i < comm_size; i++)
    {
        displs[i] = i * local_array_length;
    }

    int *sendcnts = malloc(comm_size * sizeof(int));
    for (i = 0; i < comm_size; i++)
    {
        sendcnts[i] = local_array_length;
    }

    MPI_Scatterv(array, sendcnts, displs, MPI_INT, local_array,
												local_array_length,
    											MPI_INT,
    											0x0,
    											MPI_COMM_WORLD);


    free(displs);  
    free(sendcnts);


    for (i = 0; i < array_length; i++)
    {
        
        if (i % 2 == 0)
        {

            if (rank % 2 == 0)
            {
                
                if (rank < comm_size - 1)
                {

                    front_swap(local_array, local_array_length, rank);
                }
            }
            else
            {
                if (rank - 1 >= 0)
                {
         
                    back_swap(local_array, local_array_length, rank);
                }
            }
        }
        else
        {
            if (rank % 2 != 0)
            {
                if (rank < comm_size - 1)
                {
                   
                    front_swap(local_array, local_array_length, rank);
                }
            }
            else
            {
            if (rank - 1 >= 0)
                {
                  
                    back_swap(local_array, local_array_length, rank);
                }
            }
        }
    }

  
    MPI_Gather(local_array, local_array_length, MPI_INT, array,
												local_array_length,
    											MPI_INT,
    											0x0,
    											MPI_COMM_WORLD); 

    if(rank == 0x0)
    {

		gettimeofday(&stop, 0x0);
		print_array("check", array, local_array_length);
		printf("Array length %d", array_length);
		fprintf(stdout, "\t %2.7f\n", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));
    }


    MPI_Finalize();
    return 0;
}

