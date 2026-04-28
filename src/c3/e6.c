#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse(char s[])
{
	for (unsigned i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		const char c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

static void blank_pad_left(char s[], const size_t min_width,
						   const size_t capacity)
{
	const size_t size = strlen(s);
	if (size >= min_width || min_width >= capacity) {
		return;
	}

	const size_t padding_size = min_width - size;
	for (size_t i = size + 1; i-- > 0;) {
		s[i + padding_size] = s[i];
	}

	for (size_t i = 0; i < padding_size; ++i) {
		s[i] = ' ';
	}
}

/* itoa: convert n to characters in s */
static void itoa(const int n, char s[], const size_t min_width)
{
	constexpr unsigned DECIMAL_BASE = 10;

	int i = 0;
	const int sign = n;
	unsigned n_unsigned = (n < 0) ? -n : n;

	i = 0;
	do {
		s[i++] = (char)((n_unsigned % DECIMAL_BASE) + '0');
	} while ((n_unsigned /= DECIMAL_BASE) != 0);

	if (sign < 0) {
		s[i++] = '-';
	}

	s[i] = '\0';

	reverse(s);
	blank_pad_left(s, min_width, min_width + 1);
}

//  Write a version of itoa that accepts three arguments instead of two. The
//  third argument is a minimum field width; the converted number must be padded
//  with blanks on the left if necessary to make it wide enough.
int main(void)
{
	constexpr size_t MIN_WIDTH = 512;
	char buffer[BUFSIZ];

	itoa(INT_MAX, buffer, MIN_WIDTH);
	itoa(INT_MIN, buffer, MIN_WIDTH);

	return EXIT_SUCCESS;
}
