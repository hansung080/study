#include <stdio.h>

#define BOOL  unsigned char
#define TRUE  1
#define FALSE 0

#define SORT_TYPE      unsigned char
#define INVALID_TYPE   0
#define BUBBLE_SORT    1
#define INSERTION_SORT 2

#define SWAP(x, y, t) ((t)=(x)), ((x)=(y)), ((y)=(t))

int atoi_hs(const char* str);
void init_arr(int* arr, const char** argv, int len);
void sort_arr(int* arr, int len, SORT_TYPE type);
void print_arr(const int* arr, int len);

void proc_bubble_sort(int* arr, int len);
void proc_insertion_sort(int* arr, int len);

int main(int argc, const char** argv){
	if(argc < 2){
		fprintf(stderr, "Usage: sort 912 20 1 100 4 55 ...\n");
		return 1;
	}

	int len = argc - 1;
	int arr[len];

	init_arr(arr, argv, len);	

	sort_arr(arr, len, INSERTION_SORT);

	print_arr(arr, len);

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

void sort_arr(int* arr, int len, SORT_TYPE type){
	switch(type){
	case BUBBLE_SORT:
		proc_bubble_sort(arr, len);	
		break;
	
	case INSERTION_SORT:
		proc_insertion_sort(arr, len);
		break;

	default:
		fprintf(stderr, "Sort Type Error!!");
		break;
	}
}

void print_arr(const int* arr, int len){
	int i;

	for(i = 0; i < len; i++){
		if(i == (len - 1)){
			printf("%d\n", arr[i]);

		}else{
			printf("%d ", arr[i]);
		}
	}
}

void proc_bubble_sort(int* arr, int len){
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

void proc_insertion_sort(int* arr, int len){
	int i, j, key;
	
	for(i = 1; i < len; i++){
		key = arr[i];	

		for(j = i - 1; j >= 0; j--){
			if(arr[j] > key){
				arr[j+1] = arr[j];

			}else{
				break;				
			}
		}

		arr[j+1] = key;
	}
}

