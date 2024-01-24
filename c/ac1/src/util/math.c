#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math.h"
#include "../types.h"
#include "../log.h"

int rand_between(int min, int max) {
    if (min > max) {
        fprintf(stderr, LOG_ERROR": rand_between: min(%d) must be less than or equal to max(%d)\n", min, max);
        return -1;
    }

    static volatile bool initialized = false;
    if (!initialized) {
        srand(time(NULL));
        initialized = true;
    }
    return (rand() % (max + 1 - min)) + min;
}

int square_i(int x) {
    return x * x;
}

unsigned int square_u(unsigned int x) {
    return x * x;
}

double square_d(double x) {
    return x * x;
}

/* Recursive Power
 * If n = 0:
 *   b^n = 1
 * If n is even:
 *   b^n = {b^(n/2)}^2
 * If n is odd:
 *   b^n = b * b^(n-1)
 */
double pow_rec(double b, unsigned int n) {
    if (n == 0) 
        return 1;
    else if (n % 2 == 0)
        return square(pow_rec(b, n / 2));
    else 
        return b * pow_rec(b, n - 1);
}

/* Iterative Power
 * If n = 0:
 *   a = b^n
 * If n is even:
 *   ab^n = a{b^(n/2)}^2 = a(b^2)^(n/2) = a'b'^n'
 *   a' = a
 *   b' = b^2
 *   n' = n/2
 * If n is odd:
 *   ab^n = abb^(n-1) = (ab)b^(n-1) = a'b'^n'
 *   a' = ab
 *   b' = b
 *   n' = n-1
 */
double pow_iter(double b, unsigned int n) {
    double a = 1;
    while (n) {
        if (n % 2 == 0) {
            b *= b;
            n /= 2;
        } else {
            a *= b;
            n -= 1;
        }
    }
    return a;
}

/* Remainder Theorem
 * 1. (a * b) % m = {(a % m) * b} % m
 * 2. (a * b) % m = {a * (b % m)} % m
 * 3. (a * b) % m = {(a % m) * (b % m)} % m
 */
unsigned int powmod_basic(unsigned int b, unsigned int n, unsigned int m) {
    return (unsigned int)pow(b % m, n) % m;
}

/* Recursive Power-Modulo
 * If n = 0:
 *   b^n = 1
 * If n is even:
 *   b^n % m = {b^(n/2)}^2 % m
 *           = [{b^(n/4)}^2 % m]^2 % m
 *           ...
 * If n is odd:
 *   b^n % m = b * b^(n-1) % m
 *           = b * {b * b^(n-2) % m} % m
 *           ...
 */
unsigned int powmod_rec(unsigned int b, unsigned int n, unsigned int m) {
    if (n == 0)
        return 1;
    else if (n % 2 == 0)
        return square_u(powmod_rec(b, n / 2, m)) % m;
    else
        return (b * powmod_rec(b, n - 1, m)) % m;
}

/* Iterative Power-Modulo
 * If n = 0:
 *   a = b^n % m
 * If n is even:
 *   ab^n % m = a{b^(n/2)}^2 % m = a(b^2)^(n/2) % m = a(b^2 % m)^(n/2) % m = a'b'^n' % m'
 *   a' = a
 *   b' = b^2 % m
 *   n' = n/2
 *   m' = m
 * If n is odd:
 *   ab^n % m = abb^(n-1) % m = (ab)b^(n-1) % m = (ab % m)b^(n-1) % m = a'b'^n' % m'
 *   a' = ab % m
 *   b' = b
 *   n' = n-1
 *   m' = m
 */
unsigned int powmod_iter(unsigned int b, unsigned int n, unsigned int m) {
    unsigned int a = 1;
    while (n) {
        if (n % 2 == 0) {
            b = (b * b) % m;
            n /= 2;
        } else {
            a = (a * b) % m;
            n -= 1;
        }
    }
    return a;
}
