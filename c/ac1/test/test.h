#ifndef __TEST__TEST_H__
#define __TEST__TEST_H__

#include <stddef.h>
#include <ac1/src/types.h>
#include <ac1/src/log.h>

#define T_OK_LOW green("ok")
#define T_OK_UP  green("OK")
#define T_FAILED red("FAILED")

typedef bool (*test_func)();

#pragma pack(push, 1)

typedef struct __test {
    const char* name;
    test_func func;
} test_t;

#pragma pack(pop)

test_t new_test(const char* name, test_func func);
void fail(const char* format, ...);
void fail_n(const char* format, ...);
bool assert_eq_arr(const void* got, size_t got_size, const void* want, size_t want_size, int elem_type, const char* msg);

#endif // __TEST__TEST_H__