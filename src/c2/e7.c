#include <stdio.h>
#include <stdlib.h>

unsigned invert(unsigned x, int p, int n) {
    unsigned mask = ~(~0 << n);
    int shift = p - n + 1;
    return x ^ (mask << shift);
}

// Write a function invert(x,p,n) that returns x with the n bits that begin at
// position p inverted (i.e., 1 changed into 0 and vice versa), leaving the
// others unchanged.
int main(void) {
    printf("%016b\n", invert(0b01010101, 1, 2));
    return EXIT_SUCCESS;
}
