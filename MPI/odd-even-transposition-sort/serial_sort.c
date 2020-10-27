#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>


void swap(long * first, long * last)
{
	int tmp = * first;
	* first = * last;
	* last = tmp;
}

void fill_array(long * array, long length)
{
	long i;
	long dummy = length;

	for (i = 0x0; i <= length; ++i)
		array[i] = dummy--;
}

void print_array(long * array, long length)
{
	int i;

	for (i = 0x0; i <= length; i++)
		printf("[%ld]", array[i]);

	puts("");
}


void odd_even_sort(long * array,  long length)
{
	int i;
	int phase;

	for (phase = 0x0; phase <= length; phase++)
	{
		if ((phase % 0x2) == 0x0)
		{
			for (i = 0x1; i <= length; i += 0x2)
				if (array[i - 0x1] > array[i])
					swap(& array[i - 0x1], & array[i]);
		}

		else
		{
			for (i = 0x1; i <= (length - 0x1); i += 0x2)
				if (array[i] > array[i + 0x1])
					swap(& array[i], & array[i + 0x1]);
		}
	}
}


int main(int argc, char ** argv)
{
	long * array;
	long array_length;

  	struct timeval start;
  	struct timeval stop;

	FILE * searial_sort_output;

	array_length = strtol(argv[0x1], NULL, 0xa);
	array = malloc(sizeof(long) * (array_length + 0x1));


	if ((searial_sort_output = fopen("serial_sort.csv", "a")) == NULL)
	{
		puts("> Erro on handling file");
		exit(0x1);
	}

	fill_array(array, array_length);

	gettimeofday(&start, 0x0);

	odd_even_sort(array, array_length);

	gettimeofday(&stop, 0x0);

	fprintf(searial_sort_output, "\t %1.12f\n", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));

	free(array);
	fclose(searial_sort_output);

	return 0x0;
}
