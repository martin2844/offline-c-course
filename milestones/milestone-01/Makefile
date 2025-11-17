# Makefile for Advanced Calculator Project
# Compile with: make

CC = clang
CFLAGS = -Wall -Wextra -g -std=c99
LDFLAGS = -lm  # Link math library

# Source files
SOURCES = main.c basic_ops.c advanced_ops.c number_theory.c unit_conversion.c utils.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = calculator

# Default target
all: $(TARGET)

# Build the calculator
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files
%.o: %.c calculator.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the calculator
run: $(TARGET)
	./$(TARGET)

# Install (copy to /usr/local/bin)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

# Debug build
debug: CFLAGS += -DDEBUG
debug: $(TARGET)

# Test build (with more warnings)
test: CFLAGS += -Wpedantic -Werror
test: $(TARGET)

.PHONY: all clean run install uninstall debug test