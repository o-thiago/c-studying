#include <stdio.h>
#include <stdlib.h>

static size_t str_len(const char *s)
{
	size_t i = 0;
	for (; s[i] != '\0'; ++i) {}
	return i;
}

static bool is_palindrome(const char *s)
{
	for (size_t i = 0, size = str_len(s); i < size / 2; ++i)
		if (s[i] != s[size - i - 1]) return false;
	return true;
}

// Check if a string is a palindrome without relying on the stdlib.
int main()
{
	char to_check[] = "miau";

	const char *status = "não é";
	if (is_palindrome(to_check)) status = "é";

	printf("%s %s palíndromo\n", to_check, status);
	return EXIT_SUCCESS;
}
