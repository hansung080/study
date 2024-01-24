#ifndef __UTIL__MATH_H__
#define __UTIL__MATH_H__

#define min(x, y)       (((x) < (y)) ? (x) : (y))
#define max(x, y)       (((x) > (y)) ? (x) : (y))
#define abs(x)          (((x) < 0) ? -(x) : (x))
#define swap(x, y, t)   (((t) = (x)), ((x) = (y)), ((y) = (t)))
#define swap_t(x, y, T) do { T (t) = (x); (x) = (y); (y) = (t); } while (0)

#define square square_d
#define pow    pow_iter
#define powmod powmod_iter

int rand_between(int min, int max); // including min and including max

int square_i(int x);
unsigned int square_u(unsigned int x);
double square_d(double x);

double pow_rec(double b, unsigned int n);
double pow_iter(double b, unsigned int n);

unsigned int powmod_basic(unsigned int b, unsigned int n, unsigned int m);
unsigned int powmod_rec(unsigned int b, unsigned int n, unsigned int m);
unsigned int powmod_iter(unsigned int b, unsigned int n, unsigned int m);

#endif // __UTIL__MATH_H__