#ifndef __TEST__TEST_H__
#define __TEST__TEST_H__

#include <make-sample/src/types.h>

#define C_RED    "\033[0;31m"
#define C_GREEN  "\033[0;32m"
#define C_BLUE   "\033[0;34m"
#define C_YELLOW "\033[1;33m"
#define C_RESET  "\033[0m"

#define LOG_ERROR  C_RED"ERROR"C_RESET
#define LOG_OK_LOW C_GREEN"ok"C_RESET
#define LOG_OK_UP  C_GREEN"OK"C_RESET
#define LOG_FAILED C_RED"FAILED"C_RESET

typedef bool (*test_func)();

#pragma pack(push, 1)

typedef struct __test {
    const char* name;
    test_func func;
} test;

#pragma pack(pop)

test new_test(const char* name, test_func func);

#endif // __TEST__TEST_H__
