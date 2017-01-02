#include "rank.h"

int main(int argc, const char** argv){
	if(argc < 3){
		fprintf(stderr, "Usage: rank <array> <target>\n");
		return 1;
	}

	int len = argc - 2;
	int arr[len];

	init_arr(arr, len, argv);	

	sort_arr(arr, len, ST_QUICK);

	print_arr(arr, len, "The sorted array is ");

	int target = atoi_hs(argv[argc-1]);	
	int index = search(arr, len, target, ST_BINARY_R);

	print_rank(target, index);

	return 0;
}

