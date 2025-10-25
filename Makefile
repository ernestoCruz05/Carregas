CC = gcc
CFLAGS = -Wall -Wextra -std=c2x -pedantic -g
INCLUDES = -I./src -I./src/core -I./src/data_structs -I./src/algorithms -I./src/io -I./src/utils

SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
DS_DIR = $(SRC_DIR)/data_structs
ALGO_DIR = $(SRC_DIR)/algorithms
IO_DIR = $(SRC_DIR)/io
UTILS_DIR = $(SRC_DIR)/utils

SOURCES = $(SRC_DIR)/main.c \
          $(CORE_DIR)/van.c $(CORE_DIR)/cabinet.c $(CORE_DIR)/loader.c \
          $(DS_DIR)/list.c $(DS_DIR)/vector.c \
          $(ALGO_DIR)/packing.c \
          $(IO_DIR)/file_io.c $(IO_DIR)/input.c \
          $(UTILS_DIR)/helpers.c $(UTILS_DIR)/config.c

OBJECTS = $(SOURCES:.c=.o)

TARGET = cabinet_loader

TEST_DIR = tests
TEST_SOURCES = $(TEST_DIR)/loader_validate_tests.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)
TEST_TARGET = loader_validate_tests
NON_MAIN_OBJECTS = $(filter-out $(SRC_DIR)/main.o,$(OBJECTS))

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJECTS) $(NON_MAIN_OBJECTS)
	$(CC) $(TEST_OBJECTS) $(NON_MAIN_OBJECTS) -o $(TEST_TARGET)

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(TARGET) $(TEST_TARGET)

.PHONY: clean
