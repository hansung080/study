#include "test.h"

test_t new_test(const char* name, test_func func) {
    test_t test = {name, func};
    return test;
}