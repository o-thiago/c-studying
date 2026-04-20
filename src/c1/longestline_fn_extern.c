#include <stdio.h>
#include <stdlib.h>

constexpr int MAX_INPUT_SIZE = 1028;

char current_line[MAX_INPUT_SIZE], longest_line[MAX_INPUT_SIZE];
int max_len;

int getline(void);
void copy(void);

int main() {
    int len = 0;

    max_len = 0;
    while ((len = getline()) > 0)
        if (len > max_len) {
            max_len = len;
            copy();
        }

    if (max_len > 0)
        printf("Longest line: %s\n", longest_line);
    else
        puts("No line was found.");

    return EXIT_SUCCESS;
}

int getline(void) {
    int c, i;

    for (i = 0; i < MAX_INPUT_SIZE - 1 && ((c = getchar()) != EOF && c != '\n');
         i++)
        current_line[i] = (char)c;

    if (c == '\n') current_line[i++] = (char)c;

    current_line[i] = '\0';

    return i;
}

void copy(void) {
    for (int i = 0; (longest_line[i] = current_line[i]) != '\0'; i++);
}
