#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static constexpr int decimal_base = 10;

typedef struct {
	int *elements;
	size_t count;
	size_t capacity;
} math_set;

typedef enum {
	menu_read_arr_a,
	menu_read_arr_b,
	menu_diff_a_b,
	menu_diff_b_a,
	menu_union,
	menu_union_with_repetition,
	menu_intersection,
	menu_exit,
	menu_options_count,
} menu_options;

static bool is_numeric_input(const char *buffer, const char *end);
static bool parse_unsigned(char *buffer, unsigned long *out);
static bool parse_signed(char *buffer, long *out);

static bool read_uint(char *buffer, unsigned int *out);
static bool try_read_int(char *buffer, int *out);
static void output_array(const int *arr, size_t size);

static void init_set(math_set *set, int *elements, size_t capacity);
static bool set_contains(const math_set *set, int value);
static bool set_add(math_set *set, int value);
static void set_difference(const math_set *a, const math_set *b, math_set *out);
static void set_intersection(const math_set *a, const math_set *b,
							 math_set *out);
static void set_union(const math_set *a, const math_set *b, math_set *out);
static size_t set_union_with_repetition(const math_set *a, const math_set *b,
										int *out, size_t out_capacity);
static void read_int_set(char *buffer, math_set *set);
static void output_set(const math_set *set);

int main(void)
{
	constexpr size_t array_size = 10;
	constexpr size_t out_array_size = array_size * 2;

	int raw_a[array_size];
	int raw_b[array_size];
	int raw_out[out_array_size];

	math_set set_a;
	math_set set_b;

	init_set(&set_a, raw_a, array_size);
	init_set(&set_b, raw_b, array_size);

	char buffer[BUFSIZ];
	unsigned raw_option = 0;

	while (true) {
		for (size_t i = 0; i < menu_options_count; ++i) {
			const char *options[menu_options_count] = {
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
			raw_option > menu_options_count) {
			puts("A opção selecionada é inválida!");
			continue;
		}

		const menu_options option = --raw_option;
		if (option == menu_exit) break;

		math_set out;
		init_set(&out, raw_out, out_array_size);

		switch (option) {
		case menu_read_arr_a:
			read_int_set(buffer, &set_a);
			break;
		case menu_read_arr_b:
			read_int_set(buffer, &set_b);
			break;
		case menu_diff_a_b:
			set_difference(&set_a, &set_b, &out);
			output_set(&out);
			break;
		case menu_diff_b_a:
			set_difference(&set_b, &set_a, &out);
			output_set(&out);
			break;
		case menu_union:
			set_union(&set_a, &set_b, &out);
			output_set(&out);
			break;
		case menu_union_with_repetition: {
			const size_t count = set_union_with_repetition(
				&set_a, &set_b, raw_out, out_array_size);
			output_array(raw_out, count);
			break;
		}
		case menu_intersection:
			set_intersection(&set_a, &set_b, &out);
			output_set(&out);
			break;
		case menu_options_count:
		case menu_exit:
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
	if (!fgets(buffer, BUFSIZ, stdin)) return false;

	char *end = nullptr;
	errno = 0;
	*out = strtoul(buffer, &end, decimal_base);
	return is_numeric_input(buffer, end);
}

static bool parse_signed(char *buffer, long *out)
{
	if (!fgets(buffer, BUFSIZ, stdin)) return false;

	char *end = nullptr;
	errno = 0;
	*out = strtol(buffer, &end, decimal_base);
	return is_numeric_input(buffer, end);
}

static bool read_uint(char *buffer, unsigned int *out)
{
	constexpr unsigned umax = (INT_MAX * 2U) + 1U;

	unsigned long val = 0;
	if (!parse_unsigned(buffer, &val) || (val > umax)) return false;

	*out = (unsigned int)val;
	return true;
}

static bool try_read_int(char *buffer, int *out)
{
	long val = 0;
	if (!parse_signed(buffer, &val) || val < INT_MIN || val > INT_MAX)
		return false;
	*out = (int)val;
	return true;
}

static void output_array(const int *arr, const size_t size)
{
	for (size_t i = 0; i < size; ++i) printf("vetor[%zu]=%d\n", i, arr[i]);
}

static void init_set(math_set *set, int *elements, const size_t capacity)
{
	set->elements = elements;
	set->capacity = capacity;
	set->count = 0;
}

static bool set_contains(const math_set *set, const int value)
{
	for (size_t i = 0; i < set->count; ++i)
		if (set->elements[i] == value) return true;
	return false;
}

static bool set_add(math_set *set, const int value)
{
	if (set->count >= set->capacity || set_contains(set, value)) return false;

	set->elements[set->count++] = value;
	return true;
}

static void set_difference(const math_set *a, const math_set *b, math_set *out)
{
	for (size_t i = 0; i < a->count; ++i)
		if (!set_contains(b, a->elements[i])) set_add(out, a->elements[i]);
}

static void set_intersection(const math_set *a, const math_set *b,
							 math_set *out)
{
	for (size_t i = 0; i < a->count; ++i)
		if (set_contains(b, a->elements[i])) set_add(out, a->elements[i]);
}

static void set_union(const math_set *a, const math_set *b, math_set *out)
{
	for (size_t i = 0; i < a->count; ++i) set_add(out, a->elements[i]);

	for (size_t i = 0; i < b->count; ++i) set_add(out, b->elements[i]);
}

static size_t set_union_with_repetition(const math_set *a, const math_set *b,
										int *out, const size_t out_capacity)
{
	if (a->count + b->count > out_capacity) return 0;

	for (size_t i = 0; i < a->count; ++i) *out++ = a->elements[i];

	for (size_t i = 0; i < b->count; ++i) *out++ = b->elements[i];

	return a->count + b->count;
}

static void read_int_set(char *buffer, math_set *set)
{
	set->count = 0;
	while (set->count < set->capacity) {
		int value = 0;
		printf("Digite o valor do conjunto[%zu]=", set->count);

		if (!try_read_int(buffer, &value)) {
			puts("Valor digitado inválido. Digite novamente.");
			continue;
		}

		if (!set_add(set, value)) {
			puts("Valor repetido. Conjuntos matemáticos não aceitam repetição! "
				 "Digite novamente.");
		}
	}
}

static void output_set(const math_set *set)
{
	for (size_t i = 0; i < set->count; ++i)
		printf("conjunto[%zu]=%d\n", i, set->elements[i]);
}
