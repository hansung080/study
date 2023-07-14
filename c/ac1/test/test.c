#include "test.h"

test new_test(const char* name, test_func func) {
    test t = {name, func};
    return t;
}