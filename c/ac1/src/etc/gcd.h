#ifndef __ETC__GCD_H__
#define __ETC__GCD_H__

#include "../types.h"

#define gcd gcd_mod_iter

uint gcd_sub_rec(uint a, uint b);
uint gcd_sub_iter(uint a, uint b);
uint gcd_mod_rec(uint a, uint b);
uint gcd_mod_iter(uint a, uint b);

#endif // __ETC__GCD_H__