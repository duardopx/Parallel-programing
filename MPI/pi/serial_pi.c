#include <stdio.h>
#include <stdlib.h>
#include <time.h>


long double pi_value(int points)
{
	int i;
	int hits = 0x0;
	
	srand((unsigned) time(NULL));

	for (i = 0x0; i < points; ++i)
	{
		double x = (float) rand() / RAND_MAX;
		double y = (float) rand() / RAND_MAX;

		if (x * x + y * y < 1.0)
			hits++;
	}

	return (double) (4.0 * hits/points);
}


int main(int argc, char ** argv)
{

	pi_value(100000000);

	return 0x0;
}

