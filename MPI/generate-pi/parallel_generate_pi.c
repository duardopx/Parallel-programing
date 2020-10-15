#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>


int main(int argc, char ** argv)
{

	int i;

	int hits;
	double sum_hits;
	long long points;
	long long points_per_core;
	double aproximated_pi;

	int rank;
	int comm_size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);


	hits = 0x0;
	sum_hits = 0x0;
	points = strtol(argv[0x1], NULL, 0xa);
	points_per_core = ((points) / (comm_size - 0x1));

	srand(time(NULL) + rank);

	if (rank != 0x0)
	{
		for (i = 0x1; i < points_per_core; ++i)
		{
			double x = (float) rand() / RAND_MAX;
			double y = (float) rand() / RAND_MAX;

			if (x * x + y * y < 1.0)
				hits++;
		}

		for (i = 0x0; i < comm_size; i++)
		{
			MPI_Send(&hits, 0x1, MPI_INT, i, 0x0, MPI_COMM_WORLD);
		}
	}

	else 
	{
		for (i = 0x1; i < comm_size; i++)
		{
			MPI_Recv(&hits, 0x1, MPI_INT, MPI_ANY_SOURCE, 0x0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum_hits += hits;
		}

		aproximated_pi = (double) (4.0 * sum_hits / points);

		printf("pi-> %1.12f\n", aproximated_pi);
	}

	MPI_Finalize();


	return 0x0;
}

