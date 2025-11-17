# C Course Prerequisites

## Overview
This course is designed to be completed entirely offline (perfect for plane travel!). Before starting, ensure your development environment is properly set up.

## System Requirements
- **Operating System**: macOS (any recent version)
- **Architecture**: x86_64 or ARM (Apple Silicon)
- **Terminal Access**: Built-in Terminal.app or any terminal emulator
- **Disk Space**: ~100MB for course materials and projects

## Required Software

### 1. Xcode Command Line Tools
The most important requirement - includes clang compiler, make, and essential development tools.

**Installation:**
```bash
xcode-select --install
```

**Verification:**
```bash
clang --version
make --version
```

### 2. A Text Editor
Choose one of the following (install while you have internet):

**Recommended Options:**
- **Visual Studio Code** - Free, feature-rich
  ```bash
  # Install via Homebrew (if available)
  brew install --cask visual-studio-code
  ```
- **Sublime Text** - Lightweight, fast
  ```bash
  # Install via Homebrew (if available)
  brew install --cask sublime-text
  ```
- **Vim/Nano** - Built into macOS (no installation needed)
  ```bash
  vim --version  # Should already be available
  nano --version # Should already be available
  ```

### 3. Git (Optional, for version control practice)
```bash
git --version
# If not installed, install via Xcode Command Line Tools
```

## Environment Verification Script
Create and run this script to verify your setup:

```bash
# Save as verify_setup.sh and run: bash verify_setup.sh
#!/bin/bash

echo "🔍 Verifying C Course Environment Setup..."
echo "=========================================="

# Check clang
if command -v clang &> /dev/null; then
    echo "✅ clang found: $(clang --version | head -n1)"
else
    echo "❌ clang not found. Install Xcode Command Line Tools."
    exit 1
fi

# Check make
if command -v make &> /dev/null; then
    echo "✅ make found: $(make --version | head -n1)"
else
    echo "❌ make not found. Install Xcode Command Line Tools."
    exit 1
fi

# Check text editor
editors=("code" "subl" "vim" "nano")
editor_found=false
for editor in "${editors[@]}"; do
    if command -v "$editor" &> /dev/null; then
        echo "✅ Text editor found: $editor"
        editor_found=true
        break
    fi
done

if [ "$editor_found" = false ]; then
    echo "⚠️  No common text editor found. Install VS Code, Sublime Text, or use vim/nano."
fi

# Test compilation
echo "🧪 Testing compilation..."
cat > test_compile.c << 'EOF'
#include <stdio.h>
int main() {
    printf("Hello, C Course!\\n");
    return 0;
}
EOF

if clang test_compile.c -o test_compile && ./test_compile; then
    echo "✅ Compilation test successful!"
    rm test_compile test_compile.c
else
    echo "❌ Compilation test failed."
    exit 1
fi

echo "=========================================="
echo "🎉 Environment is ready for the C course!"
echo "You can now proceed with Chapter 1."
```

## Directory Structure
Create this directory structure for your course work:

```
ccourse/
├── README.md                 # Main course file
├── prerequisites.md          # This file
├── chapters/
│   ├── chapter-01/
│   ├── chapter-02/
│   ├── ...
│   └── chapter-10/
├── milestones/
│   ├── milestone-01/
│   ├── milestone-02/
│   └── final-project/
└── solutions/
    ├── chapter-01/
    ├── chapter-02/
    ├── ...
    └── final-project/
```

**Setup commands:**
```bash
# Create the directory structure
mkdir -p ccourse/{chapters/{chapter-01..chapter-10},milestones/{milestone-01,milestone-02,final-project},solutions/{chapter-01..chapter-10,final-project}}
cd ccourse
```

## What You'll Learn
- Chapter 1: Getting Started with C
- Chapter 2: Variables and Data Types
- Chapter 3: Control Flow
- Chapter 4: Functions
- Chapter 5: Arrays and Strings
- Chapter 6: Pointers
- Chapter 7: Structures and Unions
- Chapter 8: File I/O
- Chapter 9: Memory Management
- Chapter 10: Advanced Topics

## Projects
- **Milestone 1**: Basic Calculator
- **Milestone 2**: Contact Manager
- **Final Project**: DevTools Utility Suite (useful for developers!)

## Tips for Offline Learning
1. **Download everything before you go offline**
2. **Take notes in a local text file**
3. **Experiment with code variations**
4. **Don't skip the exercises**
5. **Use the solution files when stuck**

## Compilation Quick Reference
```bash
# Compile a single file
clang program.c -o program

# Compile with warnings and debugging info
clang -Wall -Wextra -g program.c -o program

# Run the compiled program
./program

# Clean up compiled files
rm program
```

## Troubleshooting
- **"command not found: clang"** → Install Xcode Command Line Tools
- **Permission denied** → Use `chmod +x` to make scripts executable
- **Can't compile** → Check file permissions and disk space

Once everything is set up, you're ready to start Chapter 1! 🚀