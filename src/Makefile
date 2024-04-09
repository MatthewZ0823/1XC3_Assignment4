CC = gcc
CFLAGS = -Wall -Wextra -g
BUILD_DIR = build
TARGET = mySA

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(BUILD_DIR)/main.o $(BUILD_DIR)/parse_vader.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/parse_vader.o $(BUILD_DIR)/main.o

$(BUILD_DIR)/main.o: main.c parse_vader.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ -c main.c

$(BUILD_DIR)/parse_vader.o: parse_vader.c parse_vader.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ -c parse_vader.c

$(BUILD_DIR):
	mkdir $@

bruh:
	echo "bruh"

clean: 
	rm -r $(BUILD_DIR)
