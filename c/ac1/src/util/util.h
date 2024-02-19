#ifndef __UTIL__UTIL_H__
#define __UTIL__UTIL_H__

#define swap(x, y, t)       (((t) = (x)), ((x) = (y)), ((y) = (t)))
#define swap_t(x, y, type)  do { type (t) = (x); (x) = (y); (y) = (t); } while (0)
#define args_len(type, ...) (sizeof((type[]){__VA_ARGS__}) / sizeof(type))

int rand_between(int min, int max); // including min and including max

#endif // __UTIL__UTIL_H__