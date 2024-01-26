#ifndef __UTIL__ARRAY_H__
#define __UTIL__ARRAY_H__

#include <stddef.h>
#include "../types.h"

const char* arr2str(const void* arr, size_t len);
bool arr_equals(const void* arr1, size_t len1, const void* arr2, size_t len2);

#endif // __UTIL__ARRAY_H__
