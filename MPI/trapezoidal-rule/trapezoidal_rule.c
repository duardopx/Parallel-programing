#include <stdio.h>

#define F(value) (0x1 / (0x1 + (value * value)))

double trapezoidal_rule(unsigned int number_trapeze, double bigger_base, double smaller_base)
{
	int i;
	double height;
	double area;

	height = (bigger_base - smaller_base) / number_trapeze;

	area = (F(bigger_base) + F(smaller_base)) / 0x2;


	for (i = 0x1; i < number_trapeze; ++i)
		area += F(i * height + smaller_base);

	return area = (height * area)*2;
}

int main(void)
{
    double smaller = 0; 
    double bigger = 1; 
  
    unsigned int number = 20; 
  
    printf("Value of integral is %6.4f\n", trapezoidal_rule(number, bigger, smaller)); 

	return 0x0;
}
