#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "math.h"
#include "string.h"
#include "../log.h"

array_t array_new(size_t elem_size, size_t cap) {
    array_t array = {NULL, 0, 0};
    
    void* arr = malloc(elem_size * cap);
    if (arr == NULL) {
        error("array_new: failed on malloc\n");
        return array;
    }
    
    array.arr = arr;
    array.elem_size = elem_size;
    array.len = 0;
    array.cap = cap;
    return array;
}

void array_destroy(array_t* a) {
    free(a->arr);
    a->arr = NULL;
    a->elem_size = 0;
    a->len = 0;
    a->cap = 0;
}

// Array Format: [0, -1, 12, -123]
char* arr_to_str(const void* arr, size_t len, int type) {
    size_t size = 2 + ((len - 1) * 2);
    for (size_t i = 0; i < len; ++i) {
        switch (type) {
        case TYPE_INT:
            size += digit_i(((const int*)arr)[i]);
            break;
        case TYPE_UINT:
            size += digit_ui(((const uint*)arr)[i]);
            break;
        default:
            error("arr_to_str: unsupported type: %d\n", type);
            return NULL;        
        }
    }

    char* str = (char*)malloc(sizeof(char) * (size + 1));
    if (str == NULL) {
        error("arr_to_str: failed on malloc\n");
        return NULL;
    }    

    char* s = str;
    *s = '[';
    ++s;
    for (size_t i = 0; i < len; ++i) {
        switch (type) {
        case TYPE_INT:
            s += int_to_str(((const int*)arr)[i], s);
            break;
        case TYPE_UINT:
            s += uint_to_str(((const uint*)arr)[i], s);
            break;
        default:
            error("arr_to_str: unsupported type: %d\n", type);
            return NULL;        
        }

        if (i == len - 1) break;
        *s = ',';
        ++s;
        *s = ' ';
        ++s;
    }
    *s = ']';
    ++s;
    *s = '\0';
    return str;
}

char* arr_to_str_i(const int arr[], size_t len) {
    return arr_to_str(arr, len, TYPE_INT);
}

char* arr_to_str_ui(const uint arr[], size_t len) {
    return arr_to_str(arr, len, TYPE_UINT);
}

bool arr_equals(const void* arr1, size_t size1, const void* arr2, size_t size2) {
    if (arr1 == NULL || arr2 == NULL) {
        if (arr1 == NULL && arr2 == NULL) return true;
        else return false;
    }
    return size1 == size2 && memcmp(arr1, arr2, size1) == 0;
}
