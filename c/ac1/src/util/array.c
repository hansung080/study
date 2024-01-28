#include <string.h>
#include "array.h"

bool a_equals(const void* arr1, size_t len1, const void* arr2, size_t len2) {
    return len1 == len2 && memcmp(arr1, arr2, len1) == 0;
}
