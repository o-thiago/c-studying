#include <stdio.h>

#define LIMITS(T, fmt_s, fmt_u)                                                \
	{                                                                          \
		unsigned T u = 0;                                                      \
		u--; /* unsigned wrap → max value */                                   \
                                                                               \
		T max = (T)(u / 2); /* clear sign bit -> max signed value*/            \
		T min = (T)(-max - 1);                                                 \
                                                                               \
		printf(#T " signed: " fmt_s " to " fmt_s "\n", min, max);              \
		printf("unsigned " #T ": 0 to " fmt_u "\n\n", u);                      \
	}

int main(void)
{
	LIMITS(char, "%d", "%u");
	LIMITS(short, "%d", "%u");
	LIMITS(int, "%d", "%u");
	LIMITS(long, "%ld", "%lu");
	return 0;
}
