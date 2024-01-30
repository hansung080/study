#include "mul.h"

/* a la russe Algorithm
 *   x     y    result
 *  45    37    37
 *  22    74    37
 *  11   148    37 + 148
 *   5   296    37 + 148 + 296
 *   2   592    37 + 148 + 296
 *   1  1184    37 + 148 + 296 + 1184 = 1665
 */
int mul_rec(int x, int y) {
    if (x == 0 || y == 0) return 0;

    if (x > 0 && y > 0)
        return proc_mul_rec(x, y);
    else if (x < 0 && y < 0)
        return proc_mul_rec(-x, -y);
    else if (x < 0)
        return -proc_mul_rec(-x, y);
    else 
        return -proc_mul_rec(x, -y);
}

int proc_mul_rec(int x, int y) {
    if (x == 1) return y;
    return ((x % 2 == 1) ? y : 0) + mul_rec(x >> 1, y << 1);
}

int mul_iter(int x, int y) {
    if (x == 0 || y == 0) return 0;

    if (x > 0 && y > 0)
        return proc_mul_iter(x, y);
    else if (x < 0 && y < 0)
        return proc_mul_iter(-x, -y);
    else if (x < 0)
        return -proc_mul_iter(-x, y);
    else 
        return -proc_mul_iter(x, -y);
}

int proc_mul_iter(int x, int y) {
    int result = 0;
    while (x > 1) {
        result += ((x % 2 == 1) ? y : 0);
        x >>= 1;
        y <<= 1;
    }
    return result + y;
}