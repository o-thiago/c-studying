#include <stdio.h>
#include <stdlib.h>

static void squeeze(char *s1, const char *s2)
{
    unsigned i = 0;
    unsigned k = 0;

    for (i = k = 0; s1[i] != '\0'; ++i) {
	bool must_delete = false;
	for (unsigned int j = 0; s2[j] != '\0'; ++j) {
	    if (s1[i] == s2[j]) {
		must_delete = true;
		break;
	    }
	}
	if (!must_delete) {
	    s1[k++] = s1[i];
	}
    }
    s1[k] = '\0';
}

// Write an alternate version of squeeze(s1,s2) that deletes each character in
// s1 that matches any character in the string s2.
int main(void)
{
    char squeezed[] = "abcdefghijkl";
    squeeze(squeezed, "abc");

    printf("This has no abc: %s", squeezed);

    return EXIT_SUCCESS;
}
