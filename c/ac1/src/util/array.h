#ifndef __UTIL__ARRAY_H__
#define __UTIL__ARRAY_H__

#include <stddef.h>
#include "../types.h"

#define deref2(arr, columns, i, j) (*((arr) + ((i) * (columns)) + (j)))

#pragma pack(push, 1)

typedef struct __array {
    void* arr;
    size_t elem_size;
    size_t len;
    size_t cap;
} array_t;

#pragma pack(pop)

array_t array_new(size_t elem_size, size_t cap);
void array_destroy(array_t* a);

static char* arr_to_str(const void* arr, size_t len, int type);
char* arr_to_str_i(const int arr[], size_t len); // Free the returned memory.
char* arr_to_str_ui(const uint arr[], size_t len); // Free the returned memory.
bool arr_equals(const void* arr1, size_t size1, const void* arr2, size_t size2);

#endif // __UTIL__ARRAY_H__