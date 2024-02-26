#ifndef __TEST__UTIL__MATH_H__
#define __TEST__UTIL__MATH_H__

#include <ac1/src/testing/test.h>

void init_util__math(t_test_t tests[], size_t* n);
static bool test_square();
static bool test_pow();
static bool test_powmod();
static bool test_powmod_checked();
static bool test_digit();

#endif // __TEST__UTIL__MATH_H__
