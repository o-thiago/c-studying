#include <stdio.h>
#include <stdlib.h>

static const char* get_replacing_char(const int c) {
    switch (c) {
        case '\t':
            return "\\t";
        case '\b':
            return "\\b";
        case '\\':
            return "\\\\";
        default:
            return nullptr;
    }
}

int main() {
    int c = 0;
    const char* replacing_char = nullptr;

    while ((c = getchar()) != EOF) {
        replacing_char = get_replacing_char(c);

        if (replacing_char == NULL) {
            putchar(c);
            continue;
        }

        if (fputs(replacing_char, stdout) == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
