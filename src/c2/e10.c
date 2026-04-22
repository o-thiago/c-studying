#include <stdio.h>
#include <stdlib.h>

static void lower(char* str) {
    for (char* p = str; *p != '\0'; ++p) {
        *p += (*p >= 'A' && *p <= 'Z') ? 'a' - 'A' : 0;
    }
}

int main(void) {
    char s[] = "ABCDEFG";
    lower(s);

    printf("%s", s);
    return EXIT_SUCCESS;
}
