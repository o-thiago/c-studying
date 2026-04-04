#include <stdio.h>
#include <string.h>

constexpr char FAHR_STR[] = "Fahrenheit";
constexpr char CELSIUS_STR[] = "Celsius";

constexpr int LOWER = 0;
constexpr int UPPER = 300;
constexpr int STEP = 20;

int main() {
    printf("%s %s\n", FAHR_STR, CELSIUS_STR);
    for (int fahr = UPPER; fahr >= LOWER; fahr -= STEP)
        printf("%-*d %-*.1f\n", (int)strlen(FAHR_STR), fahr,
               (int)strlen(CELSIUS_STR), (5.0 / 9.0) * (fahr - 32));

    return 0;
}
