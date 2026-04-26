#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c = 0;
    bool was_blank = false;

    while ((c = getchar()) != EOF) {
	if (c == ' ') {
	    was_blank = true;
	} else if (was_blank) {
	    printf(" %c", c);
	    was_blank = false;
	} else {
	    putchar(c);
	}
    }

    return EXIT_SUCCESS;
}
