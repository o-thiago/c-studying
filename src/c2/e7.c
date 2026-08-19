#include <stdio.h>
#include <stdlib.h>

static unsigned invert(unsigned x, unsigned p, unsigned n)
{
	const unsigned mask = ~(~0U << n);
	const unsigned shift = p - n + 1U;
	return x ^ (mask << shift);
}

static constexpr unsigned int BIT_FROM = 0b01010101;

// Write a function invert(x,p,n) that returns x with the n bits that begin at
// position p inverted (i.e., 1 changed into 0 and vice versa), leaving the
// others unchanged.
int main(void)
{
	printf("%016ub\n", invert(BIT_FROM, 1, 2));
	return EXIT_SUCCESS;
}
