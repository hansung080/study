#ifndef __REVERSE_H__
#define __REVERSE_H__

#include <stdio.h>
#include <string.h>
#include "util.h"

void reverse_string(char* str);

void reverse_string(char* str){
    int len = strlen_hs(str);   
    int i;
    int temp;
    
    for(i = 0; i < (len / 2); i++){
        SWAP(str[i], str[len-1-i], temp);
    }   
}

#endif // __REVERSE_H__
