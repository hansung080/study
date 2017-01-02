#include <stdio.h>
#include "math.h"

int main(int argc, const char** argv){

	double x1 = 10.0;
	double x2 = 10.1;
	double x3 = 10.5;
	double x4 = 10.9;

	printf("round(%f)=%f\n", x1, round(x1));
	printf("round(%f)=%f\n", x2, round(x2));
	printf("round(%f)=%f\n", x3, round(x3));
	printf("round(%f)=%f\n", x4, round(x4));

	printf("floor(%f)=%f\n", x1, floor(x1));
	printf("floor(%f)=%f\n", x2, floor(x2));
	printf("floor(%f)=%f\n", x3, floor(x3));
	printf("floor(%f)=%f\n", x4, floor(x4));

	printf("ceil(%f)=%f\n", x1, ceil(x1));
	printf("ceil(%f)=%f\n", x2, ceil(x2));
	printf("ceil(%f)=%f\n", x3, ceil(x3));
	printf("ceil(%f)=%f\n", x4, ceil(x4));

	return 0;
}
