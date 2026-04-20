#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int htoi(char* str) {
    unsigned int i = 0;
    int res = 0;

    if (str[0] == '0' && toupper(str[1]) == 'X') i = 2;
    for (; str[i] != '\0'; ++i) {
        if (!isxdigit(str[i])) break;
        int c = toupper(str[i]);
        int digit = isdigit(c) ? c - '0' : (c - 'A' + 10);
        res = (res * 16) + digit;
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
