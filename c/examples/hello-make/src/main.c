#include <stdio.h>
#include "fruits/apple.h"
#include "fruits/banana.h"
#include "people/alice.h"
#include "people/bob.h"

int main(int argc, const char** argv) {
    apple();
    banana(false);
    alice();
    bob(true);
    return 0;
}