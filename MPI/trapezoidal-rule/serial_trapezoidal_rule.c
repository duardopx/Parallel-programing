#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double f(double value) { return value * value; }

int main(int argc, char ** argv)
{

  	int i;
    long long trapezoids_number;

    double height;
  	double area;

  	double lower_limit = 0.0;
  	double upper_limit = 1.0;


    trapezoids_number = strtol(argv[0x1], NULL, 0xa);

    height = (upper_limit - lower_limit) / trapezoids_number;

    area = (f(upper_limit) + f(lower_limit)) / 0x2;

    for (i = 0x1; i < (trapezoids_number - 0x1); ++i)
    {
      	area += f(lower_limit + i * height);
    }

   	area = (height * area);

    printf("Integral-> %1.12f\n", area); 
	return 0x0;
}
