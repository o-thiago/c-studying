#include <stdio.h>
#include <stdlib.h>

constexpr int FOLD_MAX_WIDTH = 128;

int main() {
    int c, current_width = 0;
    while ((c = getchar()) != EOF) {
        putchar(c);

        if (c == '\n') {
            current_width = 0;
        } else if (++current_width == FOLD_MAX_WIDTH) {
            current_width = 0;
            putchar('\n');
        }
    }
    return EXIT_SUCCESS;
}
