#ifndef __TESTING__ASSERT_H__
#define __TESTING__ASSERT_H__

#include <stddef.h>
#include "../types.h"

bool assert_eq_arr(const void* got, size_t got_size, const void* want, size_t want_size, int elem_type, const char* msg);

#endif // __TESTING__ASSERT_H__