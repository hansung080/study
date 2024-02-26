#ifndef __TEST__UTIL__STRING_H__
#define __TEST__UTIL__STRING_H__

#include <ac1/src/testing/test.h>

void init_util__string(t_test_t tests[], size_t* n);
static bool test_str_to_bool();
static bool test_bool_to_str();
static bool test_int_to_str();
static bool test_str_contains();

#endif // __TEST__UTIL__STRING_H__
