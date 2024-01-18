#ifndef __TEST__TEST_H__
#define __TEST__TEST_H__

#include <ac1/src/types.h>

#define S_RESET    "\033[0m"
#define S_RED      "\033[0;31m"
#define S_RED_BOLD "\033[1;31m"
#define S_GREEN    "\033[0;32m"
#define S_YELLOW   "\033[0;33m"
#define S_BLUE     "\033[0;34m"

#define red(text)      S_RED text S_RESET
#define red_bold(text) S_RED_BOLD text S_RESET
#define green(text)    S_GREEN text S_RESET
#define yellow(text)   S_YELLOW text S_RESET
#define blue(text)     S_BLUE text S_RESET

#define LOG_ERROR  red_bold("error")
#define LOG_OK_LOW green("ok")
#define LOG_OK_UP  green("OK")
#define LOG_FAILED red("FAILED")

typedef bool (*test_func)();

#pragma pack(push, 1)

typedef struct __test {
    const char* name;
    test_func func;
} test;

#pragma pack(pop)

test new_test(const char* name, test_func func);

#endif // __TEST__TEST_H__