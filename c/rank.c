#include <stdio.h>

typedef unsigned char BOOL;
#define TRUE  1
#define FALSE 0

#define SWAP(x, y, t) ((t)=(x)), ((x)=(y)), ((y)=(t))

typedef unsigned char SEARCH_TYPE;
#define LINEAR   1 // The Array for linear-search dosen't have to be sorted.
#define BINARY   2 // The Array for binary-search must be sorted.
#define BINARY_R 3 // The Array for binary-search-recursive must be sorted. 

#define TARGET_NOT_EXISTS   -1
#define INVALID_SEARCH_TYPE -2 

int atoi_hs(const char* str);
void init_arr(int* arr, const char** argv, int len);
void sort_arr(int* arr, int len);
void print_arr(const int* arr, int len);

int search(const int* arr, int len, int target, SEARCH_TYPE type);
int linear_search(const int* arr, int len, int target);
int binary_search(const int* arr, int len, int target);
int binary_search_r(const int* arr, int left, int right, int target);
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
	int index = search(arr, len, target, BINARY_R);

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

int search(const int* arr, int len, int target, SEARCH_TYPE type){
	int index;

	switch(type){
	case LINEAR:
		index = linear_search(arr, len, target);			
		break;
	
	case BINARY:
		index = binary_search(arr, len, target);
		break;	

	case BINARY_R:
		index = binary_search_r(arr, 0, len - 1, target);
		break;

	default:
		index = INVALID_SEARCH_TYPE;
		break;
	}

	return index;
}

int linear_search(const int* arr, int len, int target){
	int i;
	
	for(i = 0; i < len; i++){
		if(arr[i] == target){
			return i;
		}
	}
	
	return TARGET_NOT_EXISTS;
}

int binary_search(const int* arr, int len, int target){
	int left = 0;
	int right = len - 1;
	int mid;

	while(left <= right){
		mid = (left + right) / 2;

		if(arr[mid] == target){
			return mid;

		}else if(arr[mid] > target){
			right = mid - 1;

		}else{
			left = mid + 1;
		}	
	}

	return TARGET_NOT_EXISTS;
}

int binary_search_r(const int* arr, int left, int right, int target){
	if(left > right){
		return TARGET_NOT_EXISTS;
	}

	int mid = (left + right) / 2;

	if(arr[mid] == target){
		return mid;
	
	}else if(arr[mid] > target){
		return binary_search_r(arr, left, mid - 1, target);		

	}else{
		return binary_search_r(arr, mid + 1, right, target);
	}
}

void print_rank(int target, int index){
	if(index == TARGET_NOT_EXISTS){
		printf("The target [%d] dosen't exists in the array.\n", target);	

	}else if(index == INVALID_SEARCH_TYPE){
		printf("The search type is invalid.\n");

	}else{
		printf("The rank of [%d] is [%d].\n", target, index + 1);
	}
}

