#include <stdio.h>
#include "fruits/apple.h"
#include "fruits/banana.h"
#include "people/alice.h"
#include "people/bob.h"

int main(int argc, char* argv[]) {
    printf("apple: %s\n", apple(false) ? "true" : "false");
    printf("banana: %d\n", banana(0));
    printf("alice: %s\n", alice(true) ? "true" : "false");
    printf("bob: %d\n", bob(1));
    return 0;
}