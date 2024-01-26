#ifndef __ETC__PRIME_H__
#define __ETC__PRIME_H__

#include "../types.h"

#define DEFAULT_FERMAT_TIMES 20

#define is_prime is_prime_basic

#pragma pack(push, 1)

typedef struct __primes {
    unsigned int* arr;
    unsigned int len;
} primes_t;

#pragma pack(pop)

bool is_prime_basic(unsigned int n);
bool is_prime_fermat(unsigned int n); // is_prime_fermat_xx fails with Carmichael numbers.
bool is_prime_fermat_times(unsigned int n, unsigned int times);
primes_t new_primes(unsigned int max); // including max
void delete_primes(const primes_t* p);

#endif // __ETC__PRIME_H__