#include <stdio.h>
#include <stdlib.h>

static constexpr int TAB_STOP = 4;

int main() {
    int c = 0;
    int space_count = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (++space_count == TAB_STOP) {
                space_count = 0;
                putchar('\t');
            }
        } else {
            if (space_count != TAB_STOP) {
                while (space_count-- > 0) {
                    putchar(' ');
                }
            }
            space_count = 0;
            putchar(c);
        }
    }

    return EXIT_SUCCESS;
}
