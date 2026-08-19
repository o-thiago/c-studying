#include <stdio.h>
#include <stdlib.h>

static constexpr size_t array_size = 3;

static inline int *matrix_at(int *base, size_t rows, size_t cols, size_t r,
							 size_t c)
{
	if (r >= rows || c >= cols) abort();
	return base + (r * cols + c);
}

static bool read_matrix(char *input, int *matrix, size_t rows, size_t cols)
{
	constexpr int decimal_base = 10;

	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			if (fgets(input, BUFSIZ, stdin) == nullptr) return false;
			*matrix_at(matrix, rows, cols, i, j) =
				(int)strtol(input, nullptr, decimal_base);
		}
	}
	return true;
}

int main(void)
{
	char input[BUFSIZ];
	int arr[array_size * array_size] = {};

	if (!read_matrix(input, arr, array_size, array_size)) return EXIT_FAILURE;

	bool is_diagonal = true;
	for (size_t i = 0; i < array_size && (int)is_diagonal; ++i) {
		for (size_t j = 0; j < array_size; ++j) {
			int val = *matrix_at(arr, array_size, array_size, i, j);
			if (i != j && val != 0) {
				is_diagonal = false;
				break;
			}
		}
	}

	if (!is_diagonal && fputs("nao ", stdout) == EOF) return EXIT_FAILURE;
	if (fputs("eh diagonal\n", stdout) == EOF) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
