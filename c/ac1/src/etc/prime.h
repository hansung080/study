#ifndef __ETC__PRIME_H__
#define __ETC__PRIME_H__

#include "../types.h"

#define DEFAULT_FERMAT_TIMES 20

#define is_prime is_prime_basic

#pragma pack(push, 1)

typedef struct __primes {
    uint* arr;
    uint len;
    char* str;
} primes_t;

#pragma pack(pop)

bool is_prime_basic(uint n);
bool is_prime_fermat(uint n); // NOTE: is_prime_fermat_xx fails with Carmichael numbers.
bool is_prime_fermat_times(uint n, uint times);
primes_t new_primes(uint max); // including max
bool primes_equals(const primes_t* p1, const primes_t* p2);
char* primes2str(primes_t* p);
void delete_primes(primes_t* p);

#endif // __ETC__PRIME_H__