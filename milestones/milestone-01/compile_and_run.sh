#!/bin/bash

# Script to compile and run the calculator project
# Make executable with: chmod +x compile_and_run.sh

echo "Advanced Calculator - Compile and Run Script"
echo "============================================"

# Check if clang is available
if ! command -v clang &> /dev/null; then
    echo "Error: clang compiler not found. Please install Xcode Command Line Tools."
    echo "Run: xcode-select --install"
    exit 1
fi

# Compile the calculator
echo "Compiling calculator..."
clang -Wall -Wextra -g -std=c99 -lm main.c basic_ops.c advanced_ops.c number_theory.c unit_conversion.c utils.c -o calculator

if [ $? -eq 0 ]; then
    echo "✅ Compilation successful!"
    echo ""
    echo "Starting calculator..."
    echo "======================"
    ./calculator
else
    echo "❌ Compilation failed!"
    exit 1
fi