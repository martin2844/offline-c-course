# Makefile for Contact Manager Project
# Compile with: make

CC = clang
CFLAGS = -Wall -Wextra -g -std=c99

# Source files
SOURCES = main.c contact.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = contact_manager

# Default target
all: $(TARGET)

# Build the contact manager
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files
%.o: %.c contact.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f contacts.dat

# Run the contact manager
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Install (copy to /usr/local/bin)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

# Test build (with more warnings)
test: CFLAGS += -Wpedantic -Werror
test: $(TARGET)

# Create data directory
data:
	mkdir -p data

.PHONY: all clean run debug install uninstall test data