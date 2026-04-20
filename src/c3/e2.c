#include <stdio.h>
#include <stdlib.h>

char special_char_to_normal(char special_char) {
    switch (special_char) {
        case '\n':
            return 'n';
        case '\t':
            return 't';
        default:
            return '\0';
    }
}

char normal_char_to_special(char normal_char) {
    switch (normal_char) {
        case 'n':
            return '\n';
        case 't':
            return '\t';
        default:
            return '\0';
    }
}

void escape(char* s, char* t) {
    unsigned i = 0;
    for (char* ptr = s; *ptr != '\0'; ++ptr) {
        switch (*ptr) {
            case '\n':
            case '\t':
                t[i++] = '\\';
                t[i++] = special_char_to_normal(*ptr);
                break;
            default:
                t[i++] = *ptr;
                break;
        }
    }
    t[i++] = '\0';
}

void escape_rev(char* s, char* t) {
    unsigned i = 0;
    for (char* ptr = s; *ptr != '\0'; ++ptr) {
        if (*ptr != '\\') {
            t[i++] = *ptr;
            continue;
        }

        if (*(ptr + 1) == '\0') {
            t[i] = '\\';
            break;
        }

        switch (*(++ptr)) {
            case 'n':
            case 't':
                t[i++] = normal_char_to_special(*ptr);
                break;
            default:
                t[i++] = '\\';
                t[i++] = *ptr;
                break;
        }
    }

    t[i++] = '\0';
}

// Write a function escape(s, t) that converts characters like newline and
// tab into visible escape sequences like \n and \t as it copies the string
// t to s. Use a switch. Write a function for the other direction as well,
// converting escape sequences into the real characters./
int main(void) {
    char from[BUFSIZ] = "abc\ndef\t", to[BUFSIZ];

    escape(from, to);
    printf("Escaped: %s\n", to);

    escape_rev(to, from);
    printf("Escaped: %s\n", from);

    return EXIT_SUCCESS;
}
