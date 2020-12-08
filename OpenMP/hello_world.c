#include <stdio.h>
#include <omp.h>


int main(void)
{
#pragma omp parallel num_threads(10)
	{
		int rank = omp_get_thread_num();
		int thread_count = omp_get_num_threads();
		printf("Hello world from thread -> %d of %d\n", rank, thread_count);
	}
	return 0x0;
}
