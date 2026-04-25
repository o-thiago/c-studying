#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static constexpr int DECIMAL_BASE = 10;

bool is_numeric_input(const char* buffer, const char* end);
bool parse_unsigned(char* buffer, unsigned long* out);
bool parse_signed(char* buffer, long* out);

bool read_size_t(char* buffer, size_t* out);
bool read_int(char* buffer, int* out);
bool read_uint(char* buffer, unsigned* out);

void read_int_array(char* buffer, int* a, size_t size);
void output_array(int* a, size_t size);

bool array_contains(const int* arr, size_t size, int value);
size_t array_difference(const int* a, const int* b, int* out, size_t size);
size_t array_union(const int* a, const int* b, int* out, size_t size);
size_t array_union_with_repetition(const int* a, const int* b, int* out,
                                   size_t size);
size_t array_dedupe(int* a, size_t size);
size_t array_intersection(const int* a, const int* b, int* out, size_t size);

typedef enum {
    READ_ARR_A,
    READ_ARR_B,
    DIFF_A_B,
    DIFF_B_A,
    UNION_WITHOUT_REPETITION,
    UNION_WITH_REPETION,
    INTERSECTION,
    EXIT,
    OPTIONS_COUNT,
} MenuOptions;

int main(void) {
    unsigned raw_option = 0;
    MenuOptions option = OPTIONS_COUNT;

    constexpr size_t ARRAY_SIZE = 10;

    int a[ARRAY_SIZE];
    int b[ARRAY_SIZE];

    int out[ARRAY_SIZE * 2];
    size_t out_size = 0;

    char buffer[BUFSIZ];

    const char* options[OPTIONS_COUNT] = {"Gravar vetor A",
                                          "Gravar vetor B",
                                          "Diferença (A - B)",
                                          "Diferença (B - A)",
                                          "União (A ∪ B) sem repetição",
                                          "União (A ∪ B) com repetição",
                                          "Intersecção (A ∩ B)",
                                          "Sair"};

    while (option != EXIT) {
        for (size_t i = 0; i < OPTIONS_COUNT; ++i) {
            printf("%zu - %s\n", i + 1, options[i]);
        }

        printf("Digite sua opção: ");
        if (!read_uint(buffer, &raw_option) || raw_option == 0 ||
            raw_option > OPTIONS_COUNT) {
            puts("A opção selecionada é inválida!");
            continue;
        };

        switch (option = (MenuOptions)--raw_option) {
            case READ_ARR_A:
                read_int_array(buffer, a, ARRAY_SIZE);
                break;
            case READ_ARR_B:
                read_int_array(buffer, b, ARRAY_SIZE);
                break;
            case DIFF_A_B:
                out_size = array_difference(a, b, out, ARRAY_SIZE);
                output_array(out, out_size);
                break;
            case DIFF_B_A:
                out_size = array_difference(b, a, out, ARRAY_SIZE);
                output_array(out, out_size);
                break;
            case UNION_WITHOUT_REPETITION:
                out_size = array_union(a, b, out, ARRAY_SIZE);
                output_array(out, out_size);
                break;
            case UNION_WITH_REPETION:
                out_size = array_union_with_repetition(a, b, out, ARRAY_SIZE);
                output_array(out, out_size);
                break;
            case INTERSECTION:
                out_size = array_intersection(a, b, out, ARRAY_SIZE);
                output_array(out, out_size);
                break;
            case OPTIONS_COUNT:
            case EXIT:
                break;
        }

        putchar('\n');
    }

    return 0;
}

bool is_numeric_input(const char* buffer, const char* end) {
    return errno == 0 && buffer != end && (*end == '\n' || *end == '\0');
}

bool parse_unsigned(char* buffer, unsigned long* out) {
    if (!fgets(buffer, BUFSIZ, stdin)) {
        return false;
    }

    char* end = nullptr;
    errno = 0;
    *out = strtoul(buffer, &end, DECIMAL_BASE);
    return is_numeric_input(buffer, end);
}

bool parse_signed(char* buffer, long* out) {
    if (!fgets(buffer, BUFSIZ, stdin)) {
        return false;
    }

    char* end = nullptr;
    errno = 0;
    *out = strtol(buffer, &end, DECIMAL_BASE);
    return is_numeric_input(buffer, end);
}

bool read_uint(char* buffer, unsigned int* out) {
    unsigned long val = 0;
    if (!parse_unsigned(buffer, &val) || val > UINT_MAX) {
        return false;
    }
    *out = (unsigned int)val;
    return true;
}

bool read_int(char* buffer, int* out) {
    long val = 0;
    if (!parse_signed(buffer, &val) || val < INT_MIN || val > INT_MAX) {
        return false;
    }
    *out = (int)val;
    return true;
}

void read_int_array(char* buffer, int* a, const size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("Digite o valor do vetor[%zu]=", i);
        if (!read_int(buffer, &a[i])) {
            puts("Valor digitado inválido. Digite novamente.");
            --i;
        }
    }
}

void output_array(int* a, const size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("vetor[%zu]=%d\n", i, a[i]);
    }
}

bool array_contains(const int* arr, const size_t size, const int value) {
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return true;
        }
    }

    return false;
}

size_t array_difference(const int* a, const int* b, int* out,
                        const size_t size) {
    size_t count = 0;

    for (size_t i = 0; i < size; ++i) {
        if (!array_contains(b, size, a[i])) {
            out[count++] = a[i];
        }
    }

    return count;
}

size_t array_union_with_repetition(const int* a, const int* b, int* out,
                                   const size_t size) {
    for (size_t i = 0; i < size; ++i) {
        out[i] = a[i];
    }

    for (size_t i = 0; i < size; ++i) {
        out[i + size] = b[i];
    }

    return size * 2;
}

size_t array_dedupe(int* a, const size_t size) {
    size_t count = 0;

    for (size_t i = 0; i < size; ++i) {
        if (!array_contains(a, count, a[i])) {
            a[count++] = a[i];
        }
    }

    return count;
}

size_t array_intersection(const int* a, const int* b, int* out,
                          const size_t size) {
    size_t count = 0;

    for (size_t i = 0; i < size; ++i) {
        if (array_contains(b, size, a[i])) {
            out[count++] = a[i];
        }
    }

    return count;
}

size_t array_union(const int* a, const int* b, int* out, const size_t size) {
    return array_dedupe(out, array_union_with_repetition(a, b, out, size));
}
