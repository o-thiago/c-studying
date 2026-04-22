#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static constexpr int DECIMAL_THRESHOLD = 10;
static constexpr int ALPHABET_OFFSET = 10;

static void reverse(char s[]) {
    for (unsigned i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static void itob(int n, char s[], int b) {
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

    itob(72, s, 2);
    printf("%s\n", s);

    itob(15, s, 16);
    printf("%s\n", s);

    return EXIT_SUCCESS;
}
