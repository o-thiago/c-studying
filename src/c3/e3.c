#include <stdlib.h>

[[maybe_unused]] static void expand(const char *s1, char *s2)
{
    char c = 0;
    while ((c = *s1++)) {
	if (*s1 != '-' || *(s1 + 1) < c) {
	    *s2++ = c;
	    continue;
	}

	++s1; // SKIPS: '-'.
	while (c < *s1) {
	    *s2++ = c++;
	}
    }
    *s2 = '\0';
}

// Write a function expand(s1,s2) that expands shorthand notations like a-z in
// the string s1 into the equivalent complete list abc...xyz in s2. Allow for
// letters of either case and digits, and be prepared to handle cases like a-b-c
// and a-z0−9 and -a-z. Arrange that a leading or trailing - is taken literally.
int main(void) { return EXIT_SUCCESS; }
