#include <stdio.h>

#define BOOL  unsigned char
#define TRUE  1
#define FALSE 0

#define SWAP(x, y, t) ((t)=(x)), ((x)=(y)), ((y)=(t))

#define NOT_EXISTS -1

int atoi_hs(const char* str);
void init_arr(int* arr, const char** argv, int len);
void sort_arr(int* arr, int len);
void print_arr(const int* arr, int len);
int linear_search(const int* arr, int len, int target);
void print_rank(int target, int index);

int main(int argc, const char** argv){
	if(argc < 3){
		fprintf(stderr, "Usage: rank <array> <target>\n");
		return 1;
	}

	int len = argc - 2;
	int arr[len];

	init_arr(arr, argv, len);	

	sort_arr(arr, len);

	print_arr(arr, len);

	int target = atoi_hs(argv[argc-1]);	
	int index = linear_search(arr, len, target);

	print_rank(target, index);

	return 0;
}

int atoi_hs(const char* str){
	int i;
	int result = 0;

	for(i = 0; str[i] != '\0'; i++){
		result *= 10;
		result += (str[i] - '0');
	}

	return result;
}

void init_arr(int* arr, const char** argv, int len){
	int i;

	for(i = 0; i < len; i++){
		arr[i] = atoi_hs(argv[i+1]);
	}
}

// Bubble Sort
void sort_arr(int* arr, int len){
	int i, j, temp;
	BOOL swaped = TRUE;

	for(i = len - 1; i > 0 && swaped == TRUE; i--){
		swaped = FALSE;

		for(j = 0; j < i; j++){
			if(arr[j] > arr[j+1]){
				SWAP(arr[j], arr[j+1], temp);
				swaped = TRUE;
			}
		}
	}
}

void print_arr(const int* arr, int len){
	int i;
	
	printf("The sorted array is [");

	for(i = 0; i < len; i++){
		if(i == (len - 1)){
			printf("%d].\n", arr[i]);

		}else{
			printf("%d ", arr[i]);
		}
	}
}

int linear_search(const int* arr, int len, int target){
	int i;
	
	for(i = 0; i < len; i++){
		if(arr[i] == target){
			return i;
		}
	}
	
	return NOT_EXISTS;
}

void print_rank(int target, int index){
	if(index == NOT_EXISTS){
		printf("The target dosen't exists in the array.\n");	

	}else{
		printf("The rank of [%d] is [%d].\n", target, index + 1);
	}
}

