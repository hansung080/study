#include "lcm.h"
#include "gcd.h"

/* Least Common Multiple
 * A, B are positive integers, G is the greatest common divisor, and L is the least common multiple.
 *   A * B = G * L
 *   L = (A * B) / G
 */
uint lcm(uint a, uint b) {
    return (a * b) / gcd(a, b);
}
