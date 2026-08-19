#include <stdio.h>
#include <stdlib.h>

// Replace in x the n bits ending at position p with the n rightmost bits of y
static unsigned int setbits(const unsigned int x, const unsigned int p,
							const unsigned int n, const unsigned int y)
{
	// Mask with n rightmost bits set to 1
	const unsigned int mask = ~(~0U << n);

	// Align block so it ends at position p
	const unsigned int shift = p - n + 1U;

	// Clear target bits in x
	const unsigned int x_cleared = x & ~(mask << shift);

	// Take n rightmost bits of y and move into position
	const unsigned int y_bits = (y & mask) << shift;

	// Combine
	return x_cleared | y_bits;
}

static constexpr unsigned int BITS_X = 0b01010101U;
static constexpr unsigned int BITS_Y = 0b1010101010U;

/// Write a function setbits(x,p,n,y) that returns x with the n bits that begin
/// at position p set to the rightmost n bits of y, leaving the other bits
/// unchanged.
int main(void)
{
	printf("%016b\n", (int)setbits(BITS_X, 1U, 2U, BITS_Y));
	return EXIT_SUCCESS;
}
