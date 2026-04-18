#include <stdio.h>
#include <stdlib.h>

constexpr int TAB_STOP = 4;

int main() {
    int c;
    while ((c = getchar()) != EOF)
        if (c == '\t')
            for (int i = 0; i < TAB_STOP; i++) putchar(' ');
        else
            putchar(c);
    return EXIT_SUCCESS;
}
