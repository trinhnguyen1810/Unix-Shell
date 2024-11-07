# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pthread -Iinclude

# Directories and files
SRC_DIR = src
OBJ_DIR = obj
TARGET = wish
TEST_SCRIPT = test-wish.sh

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Default target: build
all: $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

# Compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if it does not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Run tests
test: $(TARGET)
	@chmod +x $(TEST_SCRIPT)
	@./$(TEST_SCRIPT)

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all test clean
