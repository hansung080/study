#include <stdio.h>
#include <stdlib.h>
#include "InfixCalculator.h"

int main(int argc, const char** argv){
	if(argc != 2){
		fprintf(stderr, "Usage : calc \"-10*(-100+200)+(22345.678/(20-10))\"\n");
		exit(-1);
	}
	
	printf("%lf\n", calcInfix(argv[1]));
	
	return 0;
}

