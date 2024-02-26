#include <ac1/src/testing/test.h>
#include "util/util.h"
#include "util/math.h"
#include "util/string.h"
#include "util/array.h"
#include "util/term.h"
#include "etc/mul.h"
#include "etc/gcd.h"
#include "etc/lcm.h"
#include "etc/prime.h"
#include "ds/linked_list.h"

int main(int argc, char* argv[]) {
    t_init_func inits[] = {
        init_util__util,
        init_util__math,
        init_util__string,
        init_util__array,
        init_util__term,
        init_etc__mul,
        init_etc__gcd,
        init_etc__lcm,
        init_etc__prime,
        init_ds__linked_list,
    };
    if (!t_start(inits, sizeof(inits) / sizeof(t_init_func), 21, argc, argv)) return 1;
    return 0;
}