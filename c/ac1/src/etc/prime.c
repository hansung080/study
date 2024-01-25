#include <stdlib.h>
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

/* Sieve of Eratosthenes
 *           2(O)   3(O)   4(X)   5(O)   6(X)   7(O)   8(X)   9(X)  10(X)
 *   11(O)  12(X)  13(O)  14(X)  15(X)  16(X)  17(O)  18(X)  19(O)  20(X)
 *   21(X)  22(X)  23(O)  24(X)  25(X)  26(X)  27(X)  28(X)  29(O)  30(X)
 */
unsigned int* get_primes(unsigned int max) {
    int len = max + 1;
    bool* not_primes = (bool*)calloc(len, sizeof(bool));
    //not_primes[1] = true;
    for (unsigned int i = 2; i < max; ++i) {
        if (not_primes[i] == true) continue;
        for (unsigned int j = i + i; j <= max; j += i) {
            not_primes[j] = true;
        }
    }

    int count = 0;
    for (int i = 1; i < len; ++i) {
        if (!not_primes[i]) ++count;
    }

    unsigned int* primes = (unsigned int*)malloc(sizeof(unsigned int) * count);
    for (int i = 1, j = 0; i < len; ++i) {
        if (!not_primes[i]) primes[j++] = i;
    }
    return primes;
}
