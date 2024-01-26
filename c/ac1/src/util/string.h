#ifndef __UTIL__STRING_H__
#define __UTIL__STRING_H__

#include "../types.h"

bool str2bool(const char* s);
const char* bool2str(bool b);
bool contains(const char* s, const char* keyword);

#endif // __UTIL__STRING_H__