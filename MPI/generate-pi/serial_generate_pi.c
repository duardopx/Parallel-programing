#include <stdio.h> 
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


int main(int argc, char ** argv)
{

	int i;
	int hits = 0x0;
	double aproximated_pi;

	long long points = strtol(argv[0x1], NULL, 0xa);

	FILE * serial_generate_pi_output;

	if ((serial_generate_pi_output = fopen("serial_pi.csv", "a")) == NULL)
	{
		fprintf(stderr, "> Can't open output file");
		exit(0x1);
	}

	srand((unsigned) time(NULL));

	for (i = 0x0; i < points; ++i)
	{
		double x = (float) rand() / RAND_MAX;
		double y = (float) rand() / RAND_MAX;

		if (x * x + y * y < 1.0)
			hits++;
	}

	aproximated_pi = (double) (4.0 * hits / points);

	printf("pi-> %1.12f\n", aproximated_pi);

	return 0x0;
}

