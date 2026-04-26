#include <stdio.h>

static constexpr unsigned int MAX_DIGITS = 10;

/* count digits, white space, others */
int main(void)
{
    unsigned int i = 0;
    unsigned int nwhite = 0;
    unsigned int nother = 0;
    unsigned int ndigit[MAX_DIGITS];

    for (i = 0; i < MAX_DIGITS; ++i) {
	ndigit[i] = 0;
    }

    for (int c = getchar(); c != EOF; c = getchar()) {
	if (c >= '0' && c <= '9') {
	    ++ndigit[c - '0'];
	} else if (c == ' ' || c == '\n' || c == '\t') {
	    ++nwhite;
	} else {
	    ++nother;
	}
    }

    printf("digits =");
    for (i = 0; i < MAX_DIGITS; ++i) {
	printf(" %d", ndigit[i]);
    }
    printf(", white space = %d, other = %d\n", nwhite, nother);

    return 0;
}
