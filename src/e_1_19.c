#include <stdio.h>
#include <stdlib.h>

void reverse(char s[]) {
    char temp;
    int j;

    for (j = 0; s[j] != '\0'; j++);
    j--;

    for (int i = 0; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    };
}

constexpr int MAX_LINE_WIDTH = 1024;

int main() {
    int c, i = 0;
    char current_line[MAX_LINE_WIDTH];

    while ((c = getchar()) != EOF)
        if (c == '\n') {
            current_line[i] = '\0';
            reverse(current_line);
            printf("%s\n", current_line);
            i = 0;
        } else
            current_line[i++] = c;

    return EXIT_SUCCESS;
}
