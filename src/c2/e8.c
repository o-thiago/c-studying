#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

unsigned rightrot(unsigned x, unsigned n) {
    int width = sizeof(x) * CHAR_BIT;
    n %= width;
    if (n == 0) return x;
    return (x >> n) | (x << (width - n));
}

// Write a function rightrot(x,n) that returns the value of the integer x
// rotated to the right by n bit positions.
int main(void) {
    printf("%016b\n", rightrot(0b01010101, 4));
    return EXIT_SUCCESS;
}
