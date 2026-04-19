#include <stdio.h>
#include <stdlib.h>

// Replace in x the n bits ending at position p with the n rightmost bits of y
unsigned setbits(unsigned x, int p, int n, unsigned y) {
    // Mask with n rightmost bits set to 1
    unsigned mask = ~(~0u << n);

    // Align block so it ends at position p
    int shift = p - n + 1;

    // Clear target bits in x
    unsigned xcleared = x & ~(mask << shift);

    // Take n rightmost bits of y and move into position
    unsigned ybits = (y & mask) << shift;

    // Combine
    return xcleared | ybits;
}

/// Write a function setbits(x,p,n,y) that returns x with the n bits that begin
/// at position p set to the rightmost n bits of y, leaving the other bits
/// unchanged.
int main(void) {
    printf("%016b\n", setbits(0b01010101, 1, 2, 0b1010101010));
    return EXIT_SUCCESS;
}
