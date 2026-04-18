#include <stdio.h>

constexpr unsigned int MAX_DIGITS = 10;

/* count digits, white space, others */
int main(void) {
    unsigned int i, nwhite, nother;
    unsigned int ndigit[MAX_DIGITS];
    int c;

    nwhite = nother = 0;
    for (i = 0; i < MAX_DIGITS; ++i) ndigit[i] = 0;

    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigit[c - '0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;

    printf("digits =");
    for (i = 0; i < 10; ++i) printf(" %d", ndigit[i]);
    printf(", white space = %d, other = %d\n", nwhite, nother);

    return 0;
}
