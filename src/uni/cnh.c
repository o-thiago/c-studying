#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static constexpr int CNH_LENGTH = 12;

// Percentage thresholds for speeding infractions
static constexpr double SPEED_LIMIT_STEP_MEDIUM = 1.2;  // 20%
static constexpr double SPEED_LIMIT_STEP_HIGH = 1.5;    // 50%

// Monetary values in cents (to avoid floating point drift)
static constexpr unsigned int FINE_VALUE_LOW = 13083;     // R$ 130,16 (Média)
static constexpr unsigned int FINE_VALUE_MEDIUM = 19523;  // R$ 195,23 (Grave)
static constexpr unsigned int FINE_VALUE_HIGH = 88041;    // R$ 880,41 (Alta)

// Penalty points
static constexpr char POINTS_LOW = 4;
static constexpr char POINTS_MEDIUM = 5;
static constexpr char POINTS_HIGH = 7;

// Overtake percentages for display
static constexpr int OVERTAKE_STEP_MEDIUM = 20;
static constexpr int OVERTAKE_STEP_HIGH = 50;

// Conversion factors
static constexpr double PERCENT_CONVERSION = 100.0;

static unsigned int multa(const char cnh_number[CNH_LENGTH],
                          const double car_velocity,
                          const double max_velocity) {
    unsigned int fine_value = 0;
    char lost_points = 0;
    char overtake_step = 0;

    if (car_velocity > max_velocity * SPEED_LIMIT_STEP_HIGH) {
        fine_value = FINE_VALUE_HIGH;
        lost_points = POINTS_HIGH;
        overtake_step = OVERTAKE_STEP_HIGH;
    } else if (car_velocity > max_velocity * SPEED_LIMIT_STEP_MEDIUM) {
        fine_value = FINE_VALUE_MEDIUM;
        lost_points = POINTS_MEDIUM;
        overtake_step = OVERTAKE_STEP_MEDIUM;
    } else if (car_velocity > max_velocity) {
        fine_value = FINE_VALUE_LOW;
        lost_points = POINTS_LOW;
    }

    if (!lost_points) {
        printf("Motorista da CNH (%s) dirigiu de acordo com as regras da via\n",
               cnh_number);
    } else {
        printf("Número da CNH: %s\n", cnh_number);
        printf("Pontos descontados na carteira: %d\n", lost_points);
        printf("Valor da multa: %.2f\n", fine_value / PERCENT_CONVERSION);
        printf(
            "A velocidade da via foi ultrapassada em %.2f%%. Sendo assim, ele "
            "ficou acima do limite ",
            (car_velocity * PERCENT_CONVERSION / max_velocity) -
                PERCENT_CONVERSION);
        if (overtake_step) {
            printf("de %d%%", overtake_step);
        } else {
            if (fputs("inicial", stdout) == EOF) {
            };
        }
        puts(" de ultrapassagem da via");
    }

    return fine_value;
}

static char* read_value(char buffer[], const int buffer_size,
                        const char message[]) {
    if (fputs(message, stdout) == EOF) {
        return nullptr;
    };

    if (fflush(stdout) == EOF) {
        return nullptr;
    };

    return fgets(buffer, buffer_size, stdin);
}

static char* read_double(char buffer[], const char message[], double* ptr) {
    char* return_value = read_value(buffer, BUFSIZ, message);

    if (return_value) {
        *ptr = strtod(buffer, nullptr);
    } else {
        puts("Número digitado foi inválido!");
    }

    return return_value;
}

static bool is_cnh_correct_length(const char cnh_number[CNH_LENGTH]) {
    return strlen(cnh_number) == CNH_LENGTH - 1;
}

static bool is_cnh_numeric(const char cnh_number[CNH_LENGTH]) {
    for (int i = 0; cnh_number[i] != '\0'; ++i) {
        if (!isdigit(cnh_number[i])) {
            return false;
        }
    }
    return true;
}

static void flush_in() {
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        ;
    }
}

int main(void) {
    char cnh_number[CNH_LENGTH];
    char buffer[BUFSIZ];
    unsigned int total_fines = 0;
    double car_velocity = NAN;
    double max_velocity = NAN;

    while (true) {
        if (!read_value(cnh_number, CNH_LENGTH, "Digite o numero da CNH: ")) {
            puts("Falha na leitura da CNH!");
            continue;
        }

        bool cnh_number_overflowed = false;
        char* optional_cnh_number_new_line_char = strchr(cnh_number, '\n');

        // Usuário ainda pode digitar '\n' no caso da input 0 ou outros que
        // não atingem o limite do buffer. Então substituimos o '\n' pelo
        // caractére de fim de string.
        if (optional_cnh_number_new_line_char) {
            *optional_cnh_number_new_line_char = '\0';
        } else {
            const int next = getchar();
            if (next != '\n' && next != EOF) {
                cnh_number_overflowed = true;

                // Consumimos os caracteres que fizeram overflow no buffer.
                flush_in();
            }
        }

        if (strcmp(cnh_number, "0") == 0) {
            break;
        }

        if (!is_cnh_correct_length(cnh_number) || (int)cnh_number_overflowed) {
            printf("A CNH precisa ter necessariamente %d caracteres!\n",
                   CNH_LENGTH - 1);
            continue;
        }

        if (!is_cnh_numeric(cnh_number)) {
            puts("A CNH precisa ser composta inteiramente por digitos!");
            continue;
        };

        if (!read_double(buffer,
                         "Digite a velocidade do carro: ", &car_velocity)) {
            continue;
        }

        if (!read_double(
                buffer, "Digite a velocidade máxima da via: ", &max_velocity)) {
            continue;
        }

        total_fines += multa(cnh_number, car_velocity, max_velocity);
    }

    printf("No total foram arrecadados R$%.2f em multas\n",
           total_fines / 100.0);

    return 0;
}
