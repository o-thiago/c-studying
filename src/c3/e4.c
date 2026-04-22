#include <stdlib.h>

#include "string.h"

static void reverse(char s[]) {
    for (unsigned i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static constexpr int DECIMAL_BASE = 10;

/* itoa: convert n to characters in s */
[[maybe_unused]] static void itoa_bad(int n, char s[]) {
    int i = 0;
    int sign = n;

    if (n < 0) { /* record sign */
        n = -n;  /* make n positive */
    }

    i = 0;
    do { /* generate digits in reverse order */
        s[i++] = (char)((n % DECIMAL_BASE) + '0'); /* get next digit */
    } while ((n /= DECIMAL_BASE) > 0); /* delete it */

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}

/* itoa: convert n to characters in s */
[[maybe_unused]] static void itoa(int n, char s[]) {
    int i = 0;
    int sign = n;

    i = 0;
    do {
        s[i++] = (char)(abs(n % DECIMAL_BASE) + '0');
    } while ((n /= DECIMAL_BASE) != 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}

// In a two’s complement number representation, our version of itoa does not
// handle the largest negative number, that is, the value of n equal to
// −(2wordsize−1).
// Explain why not. Modify it to print that value correctly, regardless of the
// machine on which it runs.
//
// ANSWER: Because in a two complements system the absolute value of INT_MIN is
// exactly one unit more than the value of INT_MAX, when we try to remove the
// sign we reach unexpected behaviour because the value is unnrepresentable.
int main(void) { return EXIT_SUCCESS; }
