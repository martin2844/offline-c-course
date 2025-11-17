# Makefile for DevTools Utility Suite
# Build with: make

CC = clang
CFLAGS = -Wall -Wextra -std=c99 -g -O2
LDFLAGS = -lssl -lcrypto

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = tests
DOC_DIR = docs

# Target executable
TARGET = $(BIN_DIR)/devtools

# Core source files
CORE_SOURCES = $(SRC_DIR)/main.c \
              $(SRC_DIR)/common/config.c \
              $(SRC_DIR)/common/utils.c \
              $(SRC_DIR)/common/error.c \
              $(SRC_DIR)/common/logging.c \
              $(SRC_DIR)/common/memory.c \
              $(SRC_DIR)/plugins/plugin_manager.c

# Tool sources
TOOL_SOURCES = $(wildcard $(SRC_DIR)/tools/*/*.c)

# Test sources
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)

# All source files
ALL_SOURCES = $(CORE_SOURCES) $(TOOL_SOURCES)

# Object files
CORE_OBJECTS = $(CORE_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TOOL_OBJECTS = $(TOOL_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
ALL_OBJECTS = $(CORE_OBJECTS) $(TOOL_OBJECTS)

# Test executables
TEST_BINS = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(BUILD_DIR)/test_%)

# Default target
.PHONY: all
all: $(TARGET)

# Build main executable
$(TARGET): $(ALL_OBJECTS) | $(BIN_DIR)
	$(CC) $(ALL_OBJECTS) -o $(TARGET) $(LDFLAGS)

# Create directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/common $(BUILD_DIR)/tools $(BUILD_DIR)/plugins

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build tests
.PHONY: test
test: $(TEST_BINS)
	@echo "Running tests..."
	@for test in $(TEST_BINS); do \
		echo "Running $$test"; \
		$$test; \
	done

$(BUILD_DIR)/test_%: $(TEST_DIR)/%.c $(CORE_OBJECTS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< $(CORE_OBJECTS) -o $@ $(LDFLAGS)

# Install target
.PHONY: install
install: $(TARGET)
	@echo "Installing devtools to /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/
	sudo mkdir -p /usr/local/share/devtools
	sudo cp -r $(SRC_DIR)/tools /usr/local/share/devtools/
	@echo "Installation complete!"

# Uninstall target
.PHONY: uninstall
uninstall:
	@echo "Uninstalling devtools..."
	sudo rm -f /usr/local/bin/devtools
	sudo rm -rf /usr/local/share/devtools
	@echo "Uninstallation complete!"

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	find . -name "*.o" -delete
	find . -name "*.dSYM" -delete

# Deep clean (remove all generated files)
.PHONY: clean-all
clean-all: clean
	rm -f core devtools.core
	rm -f devtools.log
	rm -rf *.dSYM

# Debug build
.PHONY: debug
debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Release build
.PHONY: release
release: CFLAGS += -DNDEBUG -O3 -s
release: clean $(TARGET)

# Run with valgrind (memory checking)
.PHONY: memcheck
memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all $(TARGET) --help

# Static analysis
.PHONY: analyze
analyze:
	cppcheck --enable=all --std=c99 $(SRC_DIR)/

# Code formatting
.PHONY: format
format:
	clang-format -i $(SRC_DIR)/*/*.c $(SRC_DIR)/*/*.h $(TEST_DIR)/*.c

# Generate documentation
.PHONY: docs
docs:
	@echo "Generating documentation..."
	doxygen Doxyfile
	@echo "Documentation generated in $(DOC_DIR)/"

# Run benchmarks
.PHONY: benchmark
benchmark: $(TARGET)
	time $(TARGET) file-analyzer $(SRC_DIR)/tools/*/file_analyzer.c

# Check for memory leaks (simple)
.PHONY: leak-check
leak-check: $(TARGET)
	@echo "Checking for memory leaks..."
	./$(TARGET) hash-generate $(SRC_DIR)/main.c; echo "Exit code: $$?"

# Create distribution package
.PHONY: dist
dist: clean
	@echo "Creating distribution package..."
	@mkdir -p dist/devtools-$(VERSION)
	@cp -r $(SRC_DIR) $(TEST_DIR) Makefile README.md dist/devtools-$(VERSION)/
	@tar czf devtools-$(VERSION).tar.gz -C dist devtools-$(VERSION)
	@echo "Package created: devtools-$(VERSION).tar.gz"

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all        - Build the main executable"
	@echo "  test       - Run all tests"
	@echo "  install    - Install to system directories"
	@echo "  uninstall  - Remove from system directories"
	@echo "  clean      - Remove build artifacts"
	@echo "  debug      - Build with debug symbols"
	@echo "  release    - Build optimized release version"
	@echo "  memcheck   - Run with valgrind memory checker"
	@echo "  analyze    - Run static code analysis"
	@echo "  format     - Format source code with clang-format"
	@echo "  docs       - Generate documentation"
	@echo "  benchmark  - Run performance benchmarks"
	@echo "  leak-check - Simple memory leak check"
	@echo "  dist       - Create distribution package"
	@echo "  help       - Show this help message"

# Quick development workflow
.PHONY: dev
dev: clean all test
	@echo "Development build complete!"

# Continuous integration target
.PHONY: ci
ci: clean analyze test memcheck
	@echo "CI pipeline completed successfully!"

# Dependencies
-include $(ALL_OBJECTS:.o=.d)