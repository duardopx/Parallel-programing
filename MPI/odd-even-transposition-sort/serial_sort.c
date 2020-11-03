#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>


void swap(long * first, long * last)
{
	int tmp = * first;
	* first = * last;
	* last = tmp;
}

void fill_array(long * array, long length)
{
	long i;
	srand(1337);

		for (i = 0x0; i < length; i++)
			array[i] = rand() % length;
}


void print_array(long * array, long length)
{
	int i;

	for (i = 0x0; i < length; i++)
		printf("[%ld]", array[i]);

	puts("");
}


void odd_even_sort(long * array, long array_length)
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

        for (i = 0; i < array_length - 1; i += 2)
            if (array[i] > array[i + 1])
            {
                swap(& array[i], & array[i + 0x1]);
                sorted = 0;
            }
    }
}


int main(int argc, char ** argv)
{
	long * array;
	long array_length;

  	struct timeval start;
  	struct timeval stop;


	array_length = strtol(argv[0x1], NULL, 0xa);
	array = malloc(sizeof(long) * (array_length + 0x1));

	printf("%ld", array_length);

	fill_array(array, array_length);


	gettimeofday(&start, 0x0);
	odd_even_sort(array, array_length);
	gettimeofday(&stop, 0x0);

	fprintf(stdout, "\t %2.7f\n", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));

	free(array);

	return 0x0;
}
