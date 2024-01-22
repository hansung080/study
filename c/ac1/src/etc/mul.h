#ifndef __ETC__MUL_H__
#define __ETC__MUL_H__

#define mul mul_iter

int mul_rec(int x, int y);
static int __mul_rec(int x, int y);
int mul_iter(int x, int y);
static int __mul_iter(int x, int y);

#endif // __ETC__MUL_H__