#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static constexpr int CHAR_COUNTS = 26;

int main()
{
    int c = 0;
    int char_frequency[CHAR_COUNTS];
    for (int i = 0; i < CHAR_COUNTS; ++i) {
	char_frequency[i] = 0;
    }

    while ((c = getchar()) != EOF) {
	if (isalpha(c)) {
	    ++char_frequency[c - 'a'];
	}
    }

    for (int i = 0; i < CHAR_COUNTS; i++) {
	printf("%c: ", 'a' + i);
	for (int j = 0; j < char_frequency[i]; j++) {
	    putchar('*');
	}
	putchar('\n');
    }

    return EXIT_SUCCESS;
}
