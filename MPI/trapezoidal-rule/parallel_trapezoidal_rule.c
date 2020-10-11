#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define trapezoidal_area(height, smaller_base, bigger_base) ((bigger_base + smaller_base ) * height) / 0x2

double f(value) { return value * value; }

int main(int argc, char ** argv)
{

	int i;
	/* fILE * results; */

	double area;
	double height;
    double upper_limit = 0x1;
	double lower_limit = 0x0;

    int trapezoids_number;

	int rank;
	int comm_size;

	trapezoids_number = atoi(argv[0x1]);
	height = (upper_limit - lower_limit) / trapezoids_number;

	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

	int local_trapezoids_number = trapezoids_number / comm_size;

	double local_lower_limit = lower_limit + rank * local_trapezoids_number * height;
    double local_upper_limit = local_lower_limit +  local_trapezoids_number;

	double local_area = trapezoidal_area(local_trapezoids_number, local_lower_limit, local_upper_limit);

	if (rank != 0x0)
	{
		MPI_Send(&local_area, 0x1, MPI_DOUBLE, 0x0, 0x0, MPI_COMM_WORLD);
	}

	else 
	{
		area = local_area;
		for (i = 0x1; i < comm_size; i++)
		{
			MPI_Recv(&local_area, 0x1, MPI_DOUBLE, MPI_ANY_SOURCE, 0x0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			area += local_area;
		}
		printf("Integral => %1.12f", area);
	}

	MPI_Finalize();

	return 0x0;
}
