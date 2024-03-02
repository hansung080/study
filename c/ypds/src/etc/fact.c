#include <ac1/src/etc/mul.h>
#include "fact.h"

uint fact_rec(uint n) {
    if (n == 0) return 1;
    return mul(n, fact_rec(n - 1));
}

uint fact_iter(uint n) {
    uint result = 1;
    for (; n > 1; --n) result *= n;
    return result;
}
