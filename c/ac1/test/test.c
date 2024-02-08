#include <stdio.h>
#include <stdarg.h>
#include "test.h"

test_t new_test(const char* name, test_func func) {
    test_t test = {name, func};
    return test;
}

void fail(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    fprintf(stderr, T_FAILED": ");
    vfprintf(stderr, format, ap);
    va_end(ap);
}
