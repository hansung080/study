#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "../types.h"
#include "../log.h"

int rand_between(int min, int max) {
    if (min > max) {
        error("rand_between: min(%d) must be less than or equal to max(%d)\n", min, max);
        return -1;
    }

    static volatile bool initialized = false;
    if (!initialized) {
        srand(time(NULL));
        initialized = true;
    }
    return (rand() % (max + 1 - min)) + min;
}
