CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -O2
SRC_DIR = src
BIN_DIR = bin

# Find all .c files in subdirectories
SRCS = $(shell find $(SRC_DIR) -name "*.c")
# Map src/path/file.c to bin/path/file
BINS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRCS))

.PHONY: all clean

all: $(BINS)

# The pattern rule: handles any file in any subdirectory
$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)
