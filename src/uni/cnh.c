#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

constexpr int CNH_LENGTH = 12;

unsigned int multa(const char cnh_number[CNH_LENGTH], const double car_velocity,
                   const double max_velocity) {
    unsigned int fine_value = 0;
    char lost_points = 0, overtake_step = 0;

    if (car_velocity > max_velocity * 1.5) {
        fine_value = 87462;
        lost_points = 7;
        overtake_step = 50;
    } else if (car_velocity > max_velocity * 1.2) {
        fine_value = 19869;
        lost_points = 5;
        overtake_step = 20;
    } else if (car_velocity > max_velocity) {
        fine_value = 13083;
        lost_points = 4;
    }

    if (!lost_points)
        printf("Motorista da CNH (%s) dirigiu de acordo com as regras da via\n",
               cnh_number);
    else {
        printf("Número da CNH: %s\n", cnh_number);
        printf("Pontos descontados na carteira: %d\n", lost_points);
        printf("Valor da multa: %.2f\n", fine_value / 100.0);
        printf(
            "A velocidade da via foi ultrapassada em %.2f%%. Sendo assim, ele "
            "ficou acima do limite ",
            car_velocity * 100 / max_velocity - 100);
        if (overtake_step)
            printf("de %d%%", overtake_step);
        else
            fputs("inicial", stdout);
        puts(" de ultrapassagem da via");
    }

    return fine_value;
}

char* read_value(char buffer[], const int buffer_size, const char message[]) {
    fputs(message, stdout);
    fflush(stdout);
    return fgets(buffer, buffer_size, stdin);
}

char* read_double(char buffer[], const char message[], double* ptr) {
    char* return_value = read_value(buffer, BUFSIZ, message);

    if (return_value)
        *ptr = strtod(buffer, nullptr);
    else
        puts("Número digitado foi inválido!");

    return return_value;
}

bool is_cnh_correct_length(const char cnh_number[CNH_LENGTH]) {
    return strlen(cnh_number) == CNH_LENGTH - 1;
}

bool is_cnh_numeric(const char cnh_number[CNH_LENGTH]) {
    for (int i = 0; cnh_number[i] != '\0'; ++i)
        if (!isdigit(cnh_number[i])) return false;
    return true;
}

void flush_in() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    char cnh_number[CNH_LENGTH], buffer[BUFSIZ];
    unsigned int total_fines = 0;
    double car_velocity, max_velocity;

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
        if (optional_cnh_number_new_line_char)
            *optional_cnh_number_new_line_char = '\0';
        else {
            int next = getchar();
            if (next != '\n' && next != EOF) {
                cnh_number_overflowed = true;

                // Consumimos os caracteres que fizeram overflow no buffer.
                flush_in();
            }
        }

        if (strcmp(cnh_number, "0") == 0) break;
        if (!is_cnh_correct_length(cnh_number) || cnh_number_overflowed) {
            printf("A CNH precisa ter necessariamente %d caracteres!\n",
                   CNH_LENGTH - 1);
            continue;
        }

        if (!is_cnh_numeric(cnh_number)) {
            puts("A CNH precisa ser composta inteiramente por digitos!");
            continue;
        };

        if (!read_double(buffer,
                         "Digite a velocidade do carro: ", &car_velocity))
            continue;

        if (!read_double(buffer,
                         "Digite a velocidade máxima da via: ", &max_velocity))
            continue;

        total_fines += multa(cnh_number, car_velocity, max_velocity);
    }

    printf("No total foram arrecadados R$%.2f em multas\n",
           total_fines / 100.0);
    return 0;
}
