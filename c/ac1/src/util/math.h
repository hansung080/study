#ifndef __UTIL__MATH_H__
#define __UTIL__MATH_H__

#define min(x, y)       (((x) < (y)) ? (x) : (y))
#define max(x, y)       (((x) > (y)) ? (x) : (y))
#define abs(x)          (((x) < 0) ? -(x) : (x))
#define swap(x, y, t)   (((t) = (x)), ((x) = (y)), ((y) = (t)))
#define swap_t(x, y, T) do { T (t) = (x); (x) = (y); (y) = (t); } while (0)

#endif // __UTIL__MATH_H__