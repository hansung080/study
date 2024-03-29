#include "gcd.h"
#include "../util/util.h"

/* Euclidean Algorithm
 * A, B are positive integers, and G is the greatest common divisor of them.
 * Let:
 *   A = a * G
 *   B = b * G
 * Then:
 *   A - B = (a - b) * G
 * a and b are disjoint, and (a - b) and b are disjoint.
 * Thus:
 *   1. gcd(A, B) = gcd(A - B, B)
 *   2. gcd(A, B) = gcd(B, A)
 *   3. gcd(0, B) = B
 */
uint gcd_sub_rec(uint a, uint b) {
    if (a == 0) return b;
    if (a < b) return gcd_sub_rec(b - a, a);
    else return gcd_sub_rec(a - b, b);
}

uint gcd_sub_iter(uint a, uint b) {
    uint t;
    while (a) {
        if (a < b) swap(a, b, t);
        a -= b;
    }
    return b;
}

/* Improved Euclidean Algorithm
 * Let's improve Euclidean algorithm above by modifying subtraction to modulo.
 *   gcd(A, B) = gcd(A - B, B)
 *             = gcd(A - B - B, B)
 *             = gcd(A - B - B - B, B)
 *             ...
 *             = gcd(A - B * q, B)
 *             = gcd(A % B, B)  // See Because below
 *             = gcd(B, A % B)  // Remainder(A % B) is always less than divisor(B).
 * Because:
 *   A - B * q = r
 *   A = B * q + r // r is the remainder of dividing A by B.
 *   r = A % B
 * Thus:
 *   1. gcd(A, B) = gcd(B, A % B)
 *   2. gcd(A, 0) = A
 */
uint gcd_mod_rec(uint a, uint b) {
    if (b == 0) return a;
    return gcd_mod_rec(b, a % b);
}

uint gcd_mod_iter(uint a, uint b) {
    uint t;
    while (b) {
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}
