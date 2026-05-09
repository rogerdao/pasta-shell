# xxxxx yyyyy, xxxxx yyyyy
# cssc1416, cssc1420
# CS 480, Summer 2025
# Assignment #2, Experimental Shell: "XSH"
# Filename: Makefile


CXX = g++ # C++ compiler
CXXFLAGS = -g -Wall -Wextra -std=c++11 # Compiler flags (-g for debug, -Wall and -Wextra warnings, C++ standard)
LDFLAGS = # Linker flags (e.g., -L/path/to/lib -lmylib)
TARGET = dsh # executable name
SRCS = main.cpp shell.cpp executor.cpp # Source files
OBJS = $(SRCS:.cpp=.o) # Object files (automatically generated from source files)

# The rules below are all default
# Default target: build the executable
all: $(TARGET)

# Rule to link the executable   USE TAB NOT SPACES
 	$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

# Rule to compile each source file into an object file  USE TAB NOT SPACE
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule: remove generated files
clean:
	rm -f $(TARGET) $(OBJS)
