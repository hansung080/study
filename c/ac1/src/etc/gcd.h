#ifndef __ETC__GCD_H__
#define __ETC__GCD_H__

#define gcd gcd_mod_iter

unsigned int gcd_sub_rec(unsigned int a, unsigned int b);
unsigned int gcd_sub_iter(unsigned int a, unsigned int b);
unsigned int gcd_mod_rec(unsigned int a, unsigned int b);
unsigned int gcd_mod_iter(unsigned int a, unsigned int b);

#endif // __ETC__GCD_H__