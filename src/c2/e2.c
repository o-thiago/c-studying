#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static constexpr int HEX_BASE = 16;
static constexpr int HEX_ALPHA_OFFSET = 10;

static int hex_char_to_int(char c) {
    c = toupper(c);
    return isdigit(c) ? c - '0' : (c >= 'A' && c <= 'F') ? (c - 'A' + HEX_ALPHA_OFFSET) ? -1;
}

static int htoi(const char *str) {
    unsigned i = 0;
    int res = 0;

    if (str[0] == '0' && toupper(str[1]) == 'X') {
        i = 2;
    }

    for (; str[i] != '\0'; ++i) {
        const int val = hex_char_to_int(str[i]);
        if (val == -1) {
            break;
        }
        res = (res * HEX_BASE) + val;
    }

    return res;
}

/*
 * Exercise 2-3. Write the function htoi(s), which converts a string of
 * hexadecimal digits (including an optional 0x or 0X) into its equivalent
 * integer value. The allowable digits are 0 through 9, a through f, and A
 * through F.
 */
int main(void) {
    printf("%d", htoi("123456789"));
    return EXIT_SUCCESS;
}
