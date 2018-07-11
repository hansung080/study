#include "pyramid.h"

int main(int argc, const char** argv){

	if(argc != 2 && argc != 3){
		fprintf(stderr, "Usage: pyramid <height> <r>\n");	
		return 1;
	}

	char pyramid[PY_BUF_LEN] = {0, };

	if(argc == 2 || strncmp(argv[2], "r", 1) != 0){
		make_pyramid(pyramid, atoi_hs(argv[1]));	

	}else{
		make_pyramid_rev(pyramid, atoi_hs(argv[1]));	
	}

	printf("%s", pyramid);

	return 0;
}

