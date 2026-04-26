#include <stdio.h>
#include <string.h>

static constexpr char FAHR_STR[] = "Fahrenheit";
static constexpr char CELSIUS_STR[] = "Celsius";

static constexpr int LOWER = 0;
static constexpr int UPPER = 300;
static constexpr int STEP = 20;

static constexpr double CELSIUS_RATIO = 5.0 / 9.0;
static constexpr int FAHR_OFFSET = 32;

int main()
{
    printf("%s %s\n", FAHR_STR, CELSIUS_STR);

    for (int fahr = UPPER; fahr >= LOWER; fahr -= STEP) {
	printf("%-*d %-*.1f\n", (int)strlen(FAHR_STR), fahr,
	       (int)strlen(CELSIUS_STR), CELSIUS_RATIO * (fahr - FAHR_OFFSET));
    }

    return 0;
}
