#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_sign(const char *s, int *i)
{
	const int sign = s[*i] == '-' ? -1 : 1;
	if (s[*i] == '+' || s[*i] == '-') {
		(*i)++;
	}
	return sign;
}

/* atof: convert string s to double */
static double improved_atof(const char s[])
{
	constexpr double DECIMAL_BASE = 10.0;
	double val = 0.0;
	double power = 1.0;
	int i = 0;

	for (i = 0; isspace(s[i]); i++) {
		/* skip white space */
	}

	const int sign = parse_sign(s, &i);
	for (; isdigit(s[i]); i++) {
		val = (DECIMAL_BASE * val) + (s[i] - '0');
	}

	if (s[i] == '.') {
		i++;
		for (; isdigit(s[i]); i++) {
			val = (DECIMAL_BASE * val) + (s[i] - '0');
			power *= DECIMAL_BASE;
		}
	}

	val = sign * val / power;
	if (toupper((unsigned char)s[i]) == 'E') {
		i++;
		const int exp_sign = parse_sign(s, &i);

		double exp_val = 0.0;
		for (; isdigit(s[i]); i++) {
			exp_val = (DECIMAL_BASE * exp_val) + (s[i] - '0');
		}

		val *= pow(DECIMAL_BASE, exp_sign * exp_val);
	}

	return val;
}

int main(void)
{
	printf("%.2f", improved_atof("123.45e6"));
	return EXIT_SUCCESS;
}
