#include "lcm.h"
#include "gcd.h"

/* Least Common Multiple
 * A, B are positive integers, G is the greatest common divisor, and L is the least common multiple.
 *   A * B = G * L
 *   L = (A * B) / G
*/
unsigned int lcm(unsigned int a, unsigned int b) {
    return (a * b) / gcd(a, b);
}
