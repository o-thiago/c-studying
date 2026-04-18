#include <stdio.h>
#include <stdlib.h>

int main() {
    int c, counter = 0;
    while ((c = getchar()) != EOF)
        if (c == ' ' || c == '\t' || c == '\n') ++counter;

    printf("%d\n", counter);
    return EXIT_SUCCESS;
}
