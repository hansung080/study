#include <stdio.h>
#include <string.h>

int main(int argc, const char** argv){

	if(argc != 2 && argc != 3){
		fprintf(stderr, "Usage: pyramid <height> <r>\n");	
		return 1;
	}

	return 0;
}
