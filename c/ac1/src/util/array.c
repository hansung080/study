#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "math.h"
#include "string.h"
#include "../log.h"

// Array Format: [0, -1, 12, -123]
char* arr2str(const void* arr, size_t len, int type) {
    size_t size = 2 + ((len - 1) * 2);
    for (size_t i = 0; i < len; ++i) {
        switch (type) {
        case ARR2STR_TYPE_INT:
            size += digit_i(((const int*)arr)[i]);
            break;
        case ARR2STR_TYPE_UINT:
            size += digit_ui(((const uint*)arr)[i]);
            break;
        default:
            fprintf(stderr, LOG_ERROR": arr2str: unsupported type: %d\n", type);
            return NULL;        
        }
    }

    char* str = (char*)malloc(sizeof(char) * (size + 1));
    if (str == NULL) {
        fprintf(stderr, LOG_ERROR": arr2str: failed to malloc\n");
        return NULL;
    }    

    char* s = str;
    *s = '[';
    ++s;
    for (size_t i = 0; i < len; ++i) {
        switch (type) {
        case ARR2STR_TYPE_INT:
            s += int2str(((const int*)arr)[i], s);
            break;
        case ARR2STR_TYPE_UINT:
            s += uint2str(((const uint*)arr)[i], s);
            break;
        default:
            fprintf(stderr, LOG_ERROR": arr2str: unsupported type: %d\n", type);
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

char* int_arr2str(const int* arr, size_t len) {
    return arr2str(arr, len, ARR2STR_TYPE_INT);
}

char* uint_arr2str(const uint* arr, size_t len) {
    return arr2str(arr, len, ARR2STR_TYPE_UINT);
}

bool a_equals(const void* arr1, size_t len1, const void* arr2, size_t len2) {
    return len1 == len2 && memcmp(arr1, arr2, len1) == 0;
}
