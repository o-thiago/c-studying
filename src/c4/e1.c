#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int strrindex(const char *s, const char *t)
{
    const size_t t_len = strlen(t);

    for (size_t i = strlen(s) - t_len + 1; i-- > 0;) {
	if (strncmp(&s[i], t, t_len) == 0) {
	    return (int)i;
	}
    };

    return -1;
}

// Write the function strrindex(s,t), which returns the position of the
// rightmost occurrence of t in s, or −1 if there is none.
int main(void)
{
    char out[BUFSIZ];
    strrindex("uwu", out);

    printf("%s\n", out);
    return EXIT_SUCCESS;
}
