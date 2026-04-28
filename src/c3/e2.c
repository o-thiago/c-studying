#include <stdio.h>
#include <stdlib.h>

static char special_char_to_normal(const char special_char)
{
	switch (special_char) {
	case '\n':
		return 'n';
	case '\t':
		return 't';
	default:
		return '\0';
	}
}

static char normal_char_to_special(const char normal_char)
{
	switch (normal_char) {
	case 'n':
		return '\n';
	case 't':
		return '\t';
	default:
		return '\0';
	}
}

static void escape(const char *s, char *t)
{
	while (*s) {
		switch (*s) {
		case '\n':
		case '\t':
			*t++ = '\\';
			*t++ = special_char_to_normal(*s);
			break;
		default:
			*t++ = *s;
			break;
		}
		++s;
	}
	*t = '\0';
}

static void escape_rev(const char *s, char *t)
{
	while (*s) {
		if (*s != '\\') {
			*t++ = *s;
			continue;
		}

		if (*(s + 1) == '\0') {
			*t = '\\';
			break;
		}

		switch (*(++s)) {
		case 'n':
		case 't':
			*t++ = normal_char_to_special(*s);
			break;
		default:
			*t++ = '\\';
			*t++ = *s;
			break;
		}
		++s;
	}

	*t = '\0';
}

// Write a function escape(s, t) that converts characters like newline and
// tab into visible escape sequences like \n and \t as it copies the string
// t to s. Use a switch. Write a function for the other direction as well,
// converting escape sequences into the real characters./
int main(void)
{
	char from[BUFSIZ] = "abc\ndef\t";
	char to[BUFSIZ];

	escape(from, to);
	printf("Escaped: %s\n", to);

	escape_rev(to, from);
	printf("Escaped: %s\n", from);

	return EXIT_SUCCESS;
}
