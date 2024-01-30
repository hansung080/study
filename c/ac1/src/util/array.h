#ifndef __UTIL__ARRAY_H__
#define __UTIL__ARRAY_H__

#include <stddef.h>
#include "../types.h"

#define ARR2STR_TYPE_INT  1
#define ARR2STR_TYPE_UINT 2

static char* arr2str(const void* arr, size_t len, int type);
char* int_arr2str(const int* arr, size_t len); // Free the returned memory.
char* uint_arr2str(const uint* arr, size_t len); // Free the returned memory.
bool a_equals(const void* arr1, size_t len1, const void* arr2, size_t len2);

#endif // __UTIL__ARRAY_H__