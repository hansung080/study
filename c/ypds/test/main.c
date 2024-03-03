#include <ac1/src/testing/test.h>
#include "etc/search.h"
#include "etc/fact.h"


int main(int argc, char* argv[]) {
    t_init_func inits[] = {
        init_etc__search,
        init_etc__fact,
    };
    if (!t_start(inits, sizeof(inits) / sizeof(t_init_func), 2, argc, argv)) return 1;
    return 0;
}
