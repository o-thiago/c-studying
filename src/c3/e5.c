#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse(char s[]) {
    for (unsigned i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static void itob(int n, char s[], int b) {
    constexpr int DECIMAL_THRESHOLD = 10;
    constexpr int ALPHABET_OFFSET = 10;

    char* start = s;
    while (n) {
        int rem = n % b;
        *s++ = (char)(rem < DECIMAL_THRESHOLD ? '0' + rem
                                              : 'A' + rem - ALPHABET_OFFSET);
        n /= b;
    }
    *s = '\0';
    reverse(start);
}

// Write the function itob(n,s,b) that converts the integer n into a base b
// character representation in the string s. In particular, itob(n,s,16) formats
// n as a hexadecimal integer in s./
int main(void) {
    char s[BUFSIZ];

    constexpr int BINARY_BASE = 2;
    constexpr int HEXADECIMAL_BASE = 16;

    constexpr int FIRST_INPUT = 15;
    constexpr int SECOND_INPUT = 72;

    itob(FIRST_INPUT, s, BINARY_BASE);
    printf("%s\n", s);

    itob(SECOND_INPUT, s, HEXADECIMAL_BASE);
    printf("%s\n", s);

    return EXIT_SUCCESS;
}
