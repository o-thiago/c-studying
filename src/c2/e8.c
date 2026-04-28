#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned rightrot(const unsigned x, unsigned n)
{
	constexpr int WIDTH = sizeof(x) * CHAR_BIT;
	n %= WIDTH;

	if (n == 0) {
		return x;
	}

	return (x >> n) | (x << (WIDTH - n));
}

static constexpr int BIT_FROM = 0b01010101;

// Write a function rightrot(x,n) that returns the value of the integer x
// rotated to the right by n bit positions.
int main(void)
{
	printf("%016b\n", rightrot(BIT_FROM, 4));
	return EXIT_SUCCESS;
}
