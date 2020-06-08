#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include "util.h"

void init_arr(int* arr, int len, const char** argv);
void print_arr(const int* arr, int len, const char* title);

void init_arr(int* arr, int len, const char** argv){
    int i;

    for(i = 0; i < len; i++){
        arr[i] = atoi_hs(argv[i+1]);
    }
}

void print_arr(const int* arr, int len, const char* title){
    int i;

    printf("%s[", title);
    for(i = 0; i < len; i++){
        if(i == (len - 1)){
            printf("%d]\n", arr[i]);

        }else{
            printf("%d ", arr[i]);
        }
    }
}

#endif // __ARRAY_H__
