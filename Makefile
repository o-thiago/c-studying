CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -O2
BIN_DIR = bin

.PHONY: run

run:
	@if [ -z "$(file)" ]; then \
		echo "Error: Please specify a file (e.g., make run file=main.c)"; \
		exit 1; \
	fi
	@mkdir -p $(BIN_DIR)
	$(CC) $(file) $(CFLAGS) -o $(BIN_DIR)/$(basename $(notdir $(file)))
	./$(BIN_DIR)/$(basename $(notdir $(file)))
