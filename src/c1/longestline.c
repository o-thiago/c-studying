#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c = 0;
    int longest_len = 0;
    int cur_len = 0;
    cur_len = longest_len = 0;

    while ((c = getchar()) != EOF) {
	if (c == '\n') {
	    if (cur_len > longest_len) {
		longest_len = cur_len;
	    }
	    cur_len = 0;
	} else {
	    cur_len++;
	}
    }

    if (longest_len > 0) {
	printf("The longest line was %d characters wide!\n", longest_len);
    } else {
	puts("You did not input a line!");
    }

    return EXIT_SUCCESS;
}
