#include <stdio.h>
#include <stdlib.h>

int main()
{
	char input[BUFSIZ];
	if (fgets(input, sizeof(input), stdin) == nullptr) return EXIT_FAILURE;

	const int v = (int)strtol(input, nullptr, 10);
	printf("%s\n", v % 2 == 0 ? "par" : "impar");

	return EXIT_SUCCESS;
}
