#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static constexpr int DECIMAL_BASE = 10;

typedef struct {
	int *elements;
	size_t count;
	size_t capacity;
} MathSet;

typedef enum {
	MENU_READ_ARR_A,
	MENU_READ_ARR_B,
	MENU_DIFF_A_B,
	MENU_DIFF_B_A,
	MENU_UNION,
	MENU_UNION_WITH_REPETITION,
	MENU_INTERSECTION,
	MENU_EXIT,
	MENU_OPTIONS_COUNT,
} MenuOptions;

static bool is_numeric_input(const char *buffer, const char *end);
static bool parse_unsigned(char *buffer, unsigned long *out);
static bool parse_signed(char *buffer, long *out);

static bool read_uint(char *buffer, unsigned int *out);
static bool read_int(char *buffer, int *out);
static void output_array(const int *arr, size_t size);

static void init_set(MathSet *set, int *elements, size_t capacity);
static bool set_contains(const MathSet *set, int value);
static bool set_add(MathSet *set, int value);
static void set_difference(const MathSet *a, const MathSet *b, MathSet *out);
static void set_intersection(const MathSet *a, const MathSet *b, MathSet *out);
static void set_union(const MathSet *a, const MathSet *b, MathSet *out);
static size_t set_union_with_repetition(const MathSet *a, const MathSet *b,
										int *out, size_t out_capacity);
static void read_int_set(char *buffer, MathSet *set);
static void output_set(const MathSet *set);

int main(void)
{
	constexpr size_t ARRAY_SIZE = 10;
	constexpr size_t OUT_ARRAY_SIZE = ARRAY_SIZE * 2;

	int raw_a[ARRAY_SIZE];
	int raw_b[ARRAY_SIZE];
	int raw_out[OUT_ARRAY_SIZE];

	MathSet set_a;
	MathSet set_b;

	init_set(&set_a, raw_a, ARRAY_SIZE);
	init_set(&set_b, raw_b, ARRAY_SIZE);

	char buffer[BUFSIZ];
	unsigned raw_option = 0;

	while (true) {
		for (size_t i = 0; i < MENU_OPTIONS_COUNT; ++i) {
			const char *options[MENU_OPTIONS_COUNT] = {
				"Gravar vetor A",
				"Gravar vetor B",
				"Diferença (A - B)",
				"Diferença (B - A)",
				"União (A ∪ B) sem repetição",
				"União (A ∪ B) com repetição",
				"Intersecção (A ∩ B)",
				"Sair"};
			printf("%zu - %s\n", i + 1, options[i]);
		}

		printf("Digite sua opção: ");
		if (!read_uint(buffer, &raw_option) || raw_option == 0 ||
			raw_option > MENU_OPTIONS_COUNT) {
			puts("A opção selecionada é inválida!");
			continue;
		};

		const auto option = (MenuOptions)(--raw_option);
		if (option == MENU_EXIT) {
			break;
		}

		MathSet out;
		init_set(&out, raw_out, OUT_ARRAY_SIZE);

		switch (option) {
		case MENU_READ_ARR_A:
			read_int_set(buffer, &set_a);
			break;
		case MENU_READ_ARR_B:
			read_int_set(buffer, &set_b);
			break;
		case MENU_DIFF_A_B:
			set_difference(&set_a, &set_b, &out);
			output_set(&out);
			break;
		case MENU_DIFF_B_A:
			set_difference(&set_b, &set_a, &out);
			output_set(&out);
			break;
		case MENU_UNION:
			set_union(&set_a, &set_b, &out);
			output_set(&out);
			break;
		case MENU_UNION_WITH_REPETITION: {
			const size_t count = set_union_with_repetition(
				&set_a, &set_b, raw_out, OUT_ARRAY_SIZE);
			output_array(raw_out, count);
			break;
		}
		case MENU_INTERSECTION:
			set_intersection(&set_a, &set_b, &out);
			output_set(&out);
			break;
		case MENU_OPTIONS_COUNT:
		case MENU_EXIT:
			break;
		}

		putchar('\n');
	}

	return 0;
}

static bool is_numeric_input(const char *buffer, const char *end)
{
	return errno == 0 && buffer != end && (*end == '\n' || *end == '\0');
}

static bool parse_unsigned(char *buffer, unsigned long *out)
{
	if (!fgets(buffer, BUFSIZ, stdin)) {
		return false;
	}

	char *end = nullptr;
	errno = 0;
	*out = strtoul(buffer, &end, DECIMAL_BASE);
	return is_numeric_input(buffer, end);
}

static bool parse_signed(char *buffer, long *out)
{
	if (!fgets(buffer, BUFSIZ, stdin)) {
		return false;
	}

	char *end = nullptr;
	errno = 0;
	*out = strtol(buffer, &end, DECIMAL_BASE);
	return is_numeric_input(buffer, end);
}

static bool read_uint(char *buffer, unsigned int *out)
{
	constexpr unsigned UMAX = (INT_MAX * 2U) + 1U;

	unsigned long val = 0;
	if (!parse_unsigned(buffer, &val) || (val > UMAX)) {
		return false;
	}

	*out = (unsigned int)val;
	return true;
}

static bool read_int(char *buffer, int *out)
{
	long val = 0;
	if (!parse_signed(buffer, &val) || val < INT_MIN || val > INT_MAX) {
		return false;
	}
	*out = (int)val;
	return true;
}

static void output_array(const int *arr, const size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		printf("vetor[%zu]=%d\n", i, arr[i]);
	}
}

static void init_set(MathSet *set, int *elements, const size_t capacity)
{
	set->elements = elements;
	set->capacity = capacity;
	set->count = 0;
}

static bool set_contains(const MathSet *set, const int value)
{
	for (size_t i = 0; i < set->count; ++i) {
		if (set->elements[i] == value) {
			return true;
		}
	}
	return false;
}

static bool set_add(MathSet *set, const int value)
{
	if (set->count >= set->capacity || (int)set_contains(set, value)) {
		return false;
	}

	set->elements[set->count++] = value;
	return true;
}

static void set_difference(const MathSet *a, const MathSet *b, MathSet *out)
{
	for (size_t i = 0; i < a->count; ++i) {
		if (!set_contains(b, a->elements[i])) {
			set_add(out, a->elements[i]);
		}
	}
}

static void set_intersection(const MathSet *a, const MathSet *b, MathSet *out)
{
	for (size_t i = 0; i < a->count; ++i) {
		if (set_contains(b, a->elements[i])) {
			set_add(out, a->elements[i]);
		}
	}
}

static void set_union(const MathSet *a, const MathSet *b, MathSet *out)
{
	for (size_t i = 0; i < a->count; ++i) {
		set_add(out, a->elements[i]);
	}

	for (size_t i = 0; i < b->count; ++i) {
		set_add(out, b->elements[i]);
	}
}

static size_t set_union_with_repetition(const MathSet *a, const MathSet *b,
										int *out, const size_t out_capacity)
{
	if (a->count + b->count > out_capacity) {
		return 0;
	}

	for (size_t i = 0; i < a->count; ++i) {
		*out++ = a->elements[i];
	}

	for (size_t i = 0; i < b->count; ++i) {
		*out++ = b->elements[i];
	}

	return a->count + b->count;
}

static void read_int_set(char *buffer, MathSet *set)
{
	set->count = 0;
	while (set->count < set->capacity) {
		int value = 0;
		printf("Digite o valor do conjunto[%zu]=", set->count);

		if (!read_int(buffer, &value)) {
			puts("Valor digitado inválido. Digite novamente.");
			continue;
		}

		if (!set_add(set, value)) {
			puts("Valor repetido. Conjuntos matemáticos não aceitam repetição! "
				 "Digite novamente.");
		}
	}
}

static void output_set(const MathSet *set)
{
	for (size_t i = 0; i < set->count; ++i) {
		printf("conjunto[%zu]=%d\n", i, set->elements[i]);
	}
}
