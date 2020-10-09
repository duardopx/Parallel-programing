#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, char ** argv)
{

	int i;
	FILE * results;

	int points;
	int hits;
	double sum_hits;
	double aproximated_pi;

	double x;
	double y;

	int rank;
	int comm_size;

	if ((results = fopen("parallel_pi_results.txt", "a")) == NULL)	
		exit(0x1);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);


	hits = 0x0;
	sum_hits = 0x0;
	points = (atoi(argv[0x1]));
	int points_per_core = ((points) / (comm_size - 0x1));

	srand(time(NULL) + rank);

	if (rank != 0x0)
	{
		for (i = 0x1; i < points_per_core; ++i)
		{
			x = (float) rand() / RAND_MAX;
			y = (float) rand() / RAND_MAX;

			if (x * x + y * y < 1.0)
				hits++;
		}

		for (i = 0x0; i < comm_size; i++)
		{
			MPI_Send(&hits, 0x1, MPI_DOUBLE, i, 0x0, MPI_COMM_WORLD);
		}
	}

	else 
	{
		for (i = 0x1; i < comm_size; i++)
		{
			MPI_Recv(&hits, 0x1, MPI_DOUBLE, MPI_ANY_SOURCE, 0x0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("hits -> %d\n", hits);
			sum_hits += hits;
		}

		aproximated_pi = (double) (4.0 * sum_hits / points);
		printf("pi-> %1.12f\n", aproximated_pi);
	}

	MPI_Finalize();

	fclose(results);

	return 0x0;
}


