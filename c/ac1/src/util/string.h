#ifndef __UTIL__STRING_H__
#define __UTIL__STRING_H__

#include "../types.h"

bool str2bool(const char* s);
const char* bool2str(bool b);

uint int2str(int x, char* s);
uint uint2str(uint x, char* s);

bool s_contains(const char* s, const char* keyword);

#endif // __UTIL__STRING_H__