#include <stdio.h>
#include <stdlib.h>

// Replace in x the n bits ending at position p with the n rightmost bits of y
static unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    // Mask with n rightmost bits set to 1
    const unsigned mask = ~(~0U << (unsigned)n);

    // Align block so it ends at position p
    const unsigned shift = p - n + 1;

    // Clear target bits in x
    const unsigned x_cleared = x & ~(mask << shift);

    // Take n rightmost bits of y and move into position
    const unsigned y_bits = (y & mask) << shift;

    // Combine
    return x_cleared | y_bits;
}

static constexpr int BITS_X = 0b01010101;
static constexpr int BITS_Y = 0b1010101010;

/// Write a function setbits(x,p,n,y) that returns x with the n bits that begin
/// at position p set to the rightmost n bits of y, leaving the other bits
/// unchanged.
int main(void)
{
    printf("%016b\n", setbits(BITS_X, 1, 2, BITS_Y));
    return EXIT_SUCCESS;
}
