#include <stdio.h>

int main()
{
	for (unsigned long long nc = 0; getchar() != EOF; ++nc) {
		printf("%llu\n", nc);
	}
	return 0;
}
