#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 0x64;

int main(void)
{
	char		greeting[MAX_STRING];
	int			comm_size;
	int			rank;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, & comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, & rank);

	if (rank != 0x0)
	{
		sprintf(greeting, "Grettings from process %d of %d", rank, comm_size);
		MPI_Send(greeting, (strlen(greeting) + 0x1), MPI_CHAR, 0x0, 0x0, MPI_COMM_WORLD);
	}

	else 
	{
		int i;

		printf("Greetings from process %d of %d!\n", rank, comm_size);

		for (i = 0x1; i< comm_size; i++)
		{
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, i, 0x0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", greeting);
		}

	}

    return 0x0;
}
