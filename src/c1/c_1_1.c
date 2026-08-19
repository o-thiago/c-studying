#include <stdio.h>

static constexpr unsigned int MAX_DIGITS = 10;

/* count digits, white space, others */
int main(void)
{
	unsigned int nwhite = 0;
	unsigned int nother = 0;
	unsigned int ndigit[MAX_DIGITS] = {0};

	for (int c = getchar(); c != EOF; c = getchar())
		if (c >= '0' && c <= '9') {
			const unsigned int idx = (unsigned int)(c - '0');
			if (idx < MAX_DIGITS) ++ndigit[idx];
		} else if (c == ' ' || c == '\n' || c == '\t') ++nwhite;
		else ++nother;

	printf("digits =");
	for (unsigned int i = 0; i < MAX_DIGITS; ++i) printf(" %u", ndigit[i]);
	printf(", white space = %u, other = %u\n", nwhite, nother);

	return 0;
}
