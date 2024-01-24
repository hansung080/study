#include "prime.h"
#include "../util/math.h"

bool is_prime_basic(unsigned int n) {
    if (n == 1) return false;
    if (n != 2 && n % 2 == 0) return false;
    
    for (unsigned int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

/* Fermat's Little Theorem
 * If n is a prime number, and for integer a, 0 < a < n:
 *   a^n % n = a % n = a
 *   => If n is a prime number, the expression succeeds with a 100% probability.
 *   => If n is not a prime number, the expression fails with a high probability, or succeeds with a low probability.
 * 
 * Fermat Test
 * 1. Select random integer a ranging 0 < a < n.
 * 2. If the expression succeeds, n is a prime number with a high probability.
 *    Thus, try Fermat test again to get a higher probability.
 * 3. If the expression fails, n is a not prime number with a 100% probability.
 *    Thus, quit Fermat test. 
*/
bool is_prime_fermat(unsigned int n) {
    return is_prime_fermat_times(n, DEFAULT_FERMAT_TIMES);
}

bool is_prime_fermat_times(unsigned int n, unsigned int times) {
    if (n == 1) return false;

    for (int i = 0; i < times; ++i) {
        int a = rand_between(1, n - 1);
        if (powmod(a, n, n) != a) return false;
    }
    return true;
}
