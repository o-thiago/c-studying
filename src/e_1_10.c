#include <stdio.h>
#include <stdlib.h>

char* get_replacing_char(int c) {
    if (c == '\t') return "\\t";
    if (c == '\b') return "\\b";
    if (c == '\\') return "\\\\";
    return NULL;
}

int main() {
    int c;
    char* replacing_char;

    while ((c = getchar()) != EOF)
        if ((replacing_char = get_replacing_char(c)) != NULL)
            fputs(replacing_char, stdout);
        else
            putchar(c);

    return EXIT_SUCCESS;
}
