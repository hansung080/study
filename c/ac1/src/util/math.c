#include "math.h"

double square(double x) {
    return x * x;
}

/* Recursive Power
 * If n is zero:
 *   b^n = 1
 * If n is odd:
 *   b^n = b * b^(n-1)
 * If n is even:
 *   b^n = {b^(n/2)}^2
 */
double pow_rec(double b, unsigned int n) {
    if (n == 0) 
        return 1;
    else if (n % 2 == 0)
        return square(pow_rec(b, n / 2));
    else 
        return b * pow_rec(b, n - 1);
}
