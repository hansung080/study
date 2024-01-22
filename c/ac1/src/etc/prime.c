#include "prime.h"

bool is_prime_basic(unsigned int n) {
    if (n == 1) return false;
    if (n != 2 && n % 2 == 0) return false;
    
    for (unsigned int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}
