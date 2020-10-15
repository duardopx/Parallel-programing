#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>

double f(double value) { return value * value; }

double trapezoidal_area(double height, double local_trapezoids_number, double local_lower_limit,
		double local_upper_limit)
{
	int i;
	double area;
	double x;

	area = (f(local_lower_limit) + f(local_upper_limit)) * 0.5;

	x = local_lower_limit;
	
	for (i = 0x1; i < local_trapezoids_number; i++)
	{
		x += height;
		area += f(x);
	}
	area *= height;

	return area;
}


int main(int argc, char ** argv)
{

	int i;

	double area;
	double height;
    double upper_limit = 0x1;
	double lower_limit = 0x0;

    long long trapezoids_number;

	int rank;
	int comm_size;


	trapezoids_number = strtol(argv[0x1], NULL, 0xa);
	height = (upper_limit - lower_limit) / trapezoids_number;

	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

	long long local_trapezoids_number = trapezoids_number / comm_size;

	double local_lower_limit = lower_limit + rank * local_trapezoids_number * height;
    double local_upper_limit = local_lower_limit +  local_trapezoids_number;

	double local_area = trapezoidal_area(local_trapezoids_number, local_lower_limit, local_upper_limit, height);

	if (rank != 0x0)
	{
		MPI_Send(&local_area, 0x1, MPI_DOUBLE, 0x0, 0x0, MPI_COMM_WORLD);
	}

	else 
	{
		area = local_area;

		for (i = 0x1; i < comm_size; i++)
		{
			MPI_Recv(&local_area, 0x1, MPI_DOUBLE, i, 0x0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			area += local_area;

			printf("Area-> %f", area);
		}
	}

	MPI_Finalize();

	return 0x0;
}

