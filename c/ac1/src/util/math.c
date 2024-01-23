#include "math.h"

double square(double x) {
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
