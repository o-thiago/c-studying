#include <stdio.h>
#include <stdlib.h>

int main()
{
	int c = 0;

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			putchar(c);
		} else {
			putchar((c == ' ' || c == '\t' || c == '\b') ? '\n' : '*');
		}
	}

	return EXIT_SUCCESS;
}
