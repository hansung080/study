#include "search.h"

long lsearch_i(const int arr[], long len, int elem) {
    for (long i = 0; i < len; ++i)
        if (arr[i] == elem) return i;
    return -1;
}

long bsearch_i(const int arr[], long len, int elem) {
    long start = 0;
    long end = len - 1;
    long mid;
    while (start <= end) {
        mid = (start + end) / 2;
        if (elem == arr[mid])
            return mid;
        else if (elem < arr[mid])
            end = mid - 1;
        else
            start = mid + 1;
    }
    return -1;
}
