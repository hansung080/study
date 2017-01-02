#ifndef __RANK_H__
#define __RANK_H__

#include <stdio.h>
#include "array.h"
#include "sort.h"

typedef unsigned char SEARCH_TYPE;
#define ST_LINEAR   1 // The Array for linear-search dosen't have to be sorted.
#define ST_BINARY   2 // The Array for binary-search must be sorted.
#define ST_BINARY_R 3 // The Array for binary-search-recursive must be sorted. 

#define TARGET_NOT_EXISTS   -1
#define INVALID_SEARCH_TYPE -2 

int search(const int* arr, int len, int target, SEARCH_TYPE type);
int linear_search(const int* arr, int len, int target);
int binary_search(const int* arr, int len, int target);
int binary_search_r(const int* arr, int left, int right, int target);
void print_rank(int target, int index);

int search(const int* arr, int len, int target, SEARCH_TYPE type){
    int index;

    switch(type){
    case ST_LINEAR:
        index = linear_search(arr, len, target);
        break;

    case ST_BINARY:
        index = binary_search(arr, len, target);
        break;

    case ST_BINARY_R:
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

#endif // __RANK_H__
