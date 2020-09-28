#include <stdio.h>
#include <mpi.h>


int main(void)
{
	int rank;
	int comm_size;

	MPI_Init(NULL, NULL);

	/* Number of process */
	MPI_Comm_size(MPI_COMM_WORLD, & comm_size); 

	/* Number of current process */
	MPI_Comm_rank(MPI_COMM_WORLD, & rank); 


	printf("Proc %d of %d Hello world\n", rank, comm_size);

	MPI_Finalize();
	
	return 0;
}
