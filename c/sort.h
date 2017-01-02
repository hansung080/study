#ifndef __SORT_H__
#define __SORT_H__

#include <stdio.h>
#include "type.h"
#include "util.h"
#include "array.h"

typedef unsigned char SORT_TYPE;
#define ST_BUBBLE     1
#define ST_INSERTION  2
#define ST_QUICK      3

void sort_arr(int* arr, int len, SORT_TYPE type);
void proc_bubble_sort(int* arr, int len);
void proc_insertion_sort(int* arr, int len);
void proc_quick_sort(int* arr, int left, int right);
int partition(int* arr, int left, int right);

void sort_arr(int* arr, int len, SORT_TYPE type){
    switch(type){
    case ST_BUBBLE:
        proc_bubble_sort(arr, len);
        break;

    case ST_INSERTION:
        proc_insertion_sort(arr, len);
        break;

    case ST_QUICK:
        proc_quick_sort(arr, 0, len - 1);
        break;

    default:
        fprintf(stderr, "Sort Type Error!!");
        break;
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

void proc_quick_sort(int* arr, int left, int right){
    if(left <= right){
        int pivot = partition(arr, left, right);
        proc_quick_sort(arr, left, pivot - 1);
        proc_quick_sort(arr, pivot + 1, right);
    }
}

int partition(int* arr, int left, int right){
    int pivot = left;
    int low = left + 1;
    int high = right;
    int temp;

    while(low <= high){
        while(arr[low] <= arr[pivot] && low <= right){
            low++;
        }

        while(arr[high] >= arr[pivot] && high >= left + 1){
            high--;
        }

        if(low <= high){
            SWAP(arr[low], arr[high], temp);
        }
    }

    SWAP(arr[pivot], arr[high], temp);

    return high;
}

#endif // __SORT_H__ 
