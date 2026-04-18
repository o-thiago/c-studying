CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -O2
BIN_DIR = bin

# Usage: make run SRC=src/entab.c
run:
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN_DIR)/$(basename $(notdir $(SRC)))
	@./$(BIN_DIR)/$(basename $(notdir $(SRC)))
