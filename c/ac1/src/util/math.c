#include "math.h"

int square_i(int x) {
    return x * x;
}

uint square_ui(uint x) {
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
double pow_rec(double b, uint n) {
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
double pow_iter(double b, uint n) {
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
uint powmod_basic(uint b, uint n, uint m) {
    return (uint)pow_(b % m, n) % m;
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
uint powmod_rec(uint b, uint n, uint m) {
    if (n == 0)
        return 1;
    else if (n % 2 == 0)
        return square_ui(powmod_rec(b, n / 2, m)) % m;
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
uint powmod_iter(uint b, uint n, uint m) {
    uint a = 1;
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

uint sqmod_checked(uint x, uint m) {
    uint result = (x * x) % m;
    if (x != 1 && x != m - 1 && result == 1) return 0;
    return result;
}

uint powmod_checked_rec(uint b, uint n, uint m) {
    if (n == 0)
        return 1;
    else if (n % 2 == 0)
        return sqmod_checked(powmod_rec(b, n / 2, m), m);
    else
        return (b * powmod_rec(b, n - 1, m)) % m;
}

uint powmod_checked_iter(uint b, uint n, uint m) {
    uint a = 1;
    while (n) {
        if (n % 2 == 0) {
            b = sqmod_checked(b, m);
            n /= 2;
        } else {
            a = (a * b) % m;
            n -= 1;
        }
    }
    return a;
}

uint digit_i(int x) {
    if (x < 0) return digit_ui(-x) + 1;
    else return digit_ui(x);
}

uint digit_ui(uint x) {
    uint d = 1;
    while (x /= 10) ++d;
    return d;
}