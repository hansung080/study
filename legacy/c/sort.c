#include "sort.h"

int main(int argc, const char** argv){
	if(argc < 2){
		fprintf(stderr, "Usage: sort <array>\n");
		return 1;
	}

	int len = argc - 1;
	int arr[len];

	init_arr(arr, len, argv);	

	sort_arr(arr, len, ST_QUICK);

	print_arr(arr, len, "");

	return 0;
}

