CC = gcc
CFLAGS = -Wall -Wextra -std=c23 -pedantic -g
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

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean
