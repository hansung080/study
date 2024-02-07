#ifndef __UTIL__MATH_H__
#define __UTIL__MATH_H__

#include "../types.h"

#define min(x, y)       (((x) < (y)) ? (x) : (y))
#define max(x, y)       (((x) > (y)) ? (x) : (y))
#define abs_(x)         (((x) < 0) ? -(x) : (x))
#define swap(x, y, t)   (((t) = (x)), ((x) = (y)), ((y) = (t)))
#define swap_t(x, y, T) do { T (t) = (x); (x) = (y); (y) = (t); } while (0)

#define square         square_d
#define pow_           pow_iter
#define powmod         powmod_iter
#define powmod_checked powmod_checked_iter

int rand_between(int min, int max); // including min and including max

int square_i(int x);
uint square_ui(uint x);
double square_d(double x);

double pow_rec(double b, uint n);
double pow_iter(double b, uint n);

uint powmod_basic(uint b, uint n, uint m);
uint powmod_rec(uint b, uint n, uint m);
uint powmod_iter(uint b, uint n, uint m);

/* Functions for Miller-Rabin Primality Test */
uint sqmod_checked(uint x, uint m);
uint powmod_checked_rec(uint b, uint n, uint m);
uint powmod_checked_iter(uint b, uint n, uint m);

uint digit_i(int x);
uint digit_ui(uint x);

#endif // __UTIL__MATH_H__