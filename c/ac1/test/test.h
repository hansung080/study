#ifndef __TEST__TEST_H__
#define __TEST__TEST_H__

#include <ac1/src/types.h>
#include <ac1/src/log.h>

typedef bool (*test_func)();

#pragma pack(push, 1)

typedef struct __test {
    const char* name;
    test_func func;
} test_t;

#pragma pack(pop)

test_t new_test(const char* name, test_func func);

#endif // __TEST__TEST_H__