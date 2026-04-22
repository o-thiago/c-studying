#include <stdio.h>
#include <stdlib.h>

static unsigned invert(unsigned x, int p, int n) {
    unsigned mask = ~(~0U << (unsigned)n);
    unsigned shift = p - n + 1;
    return x ^ (mask << shift);
}

static constexpr int BIT_FROM = 0b01010101;

// Write a function invert(x,p,n) that returns x with the n bits that begin at
// position p inverted (i.e., 1 changed into 0 and vice versa), leaving the
// others unchanged.
int main(void) {
    printf("%016b\n", invert(BIT_FROM, 1, 2));
    return EXIT_SUCCESS;
}
