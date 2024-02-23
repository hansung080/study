#ifndef __UTIL__STRING_H__
#define __UTIL__STRING_H__

#include "../types.h"

bool str_to_bool(const char* s);
const char* bool_to_str(bool b);
uint int_to_str(int x, char* s);
uint uint_to_str(uint x, char* s);

bool str_contains(const char* s, const char* keyword);
char* str_to_printable(char* s);

#endif // __UTIL__STRING_H__