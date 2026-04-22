CC ?= gcc
CFLAGS ?= -std=c23 -O2 -Wall -Wextra
SRC_DIR := src
BIN_DIR := bin

SRCS := $(shell find $(SRC_DIR) -name "*.c" | sort)
BINS := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRCS))

.PHONY: all clean

all: $(BINS)

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@ -lm

clean:
	rm -rf $(BIN_DIR)
