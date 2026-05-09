Assignment 2, Experimental Shell

Collaborators:
xxxxx yyyyy - cssc1416
xxxxx yyyyy - cssc1420

Class: CS 480, Summer 2025
Filename: README.txt

Account to be used for testing: cssc1420 (xxxxx yyyyy)

DESCRIPTION

This program implements XSH (Experimental Shell), a minimal Unix shell that provides basic command execution and piping functionality.

FILES MANIFEST

The following files are included in the program:
main.cpp - Entry point following the shell lifecycle (init, loop)
shell.h - Header file containing all function declarations and includes
shell.cpp - Core shell functions including main loop, command parsing, built-in commands, and environment variable handling
executor.cpp - Pipeline execution and process management
Makefile - Build configuration that creates the dsh executable
README.txt - This documentation file

COMPILATION INSTRUCTIONS

1. Navigate to the a2 directory
2. Clean up any pre-generated files using "make clean"
3. Compile the project using the make command
4. The executable "dsh" will then be created in the current directory

OPERATING INSTRUCTIONS

Run the program with ./dsh

Requirements:
- Must be run from the a2 directory
- Needs a POSIX-compliant system with fork(), exec(), and pipe() support
- No command line arguments are required

Output:
- Interactive shell prompt showing "username% " where username is detected from environment
- Command execution output displayed to terminal
- Error messages for invalid or non-existent commands
- Graceful exit when "exit" command is entered

Valid Input Formats:
- username% executablefilename
- username% executablefilename argument (only one argument)
- username% executablefilename | executablefilename
- username% executablefilename | executablefilename | executablefilename (any number of pipes)
- username% exit

DESIGN DECISIONS

Code Architecture:
Modular Design: Main function kept short as a list of function calls
Focused Tasks: Parsing, execution, and environment handling separated into dedicated functions

Environment Variable Integration:
Username Detection: Checks USER environment variable first, then LOGNAME as fallback if needed
Dynamic Prompt: Uses actual username instead of a hardcoded value
Fallback Strategy: Defaults to "cssc0000%" if no environment variables are found

Tokenizing/Parsing:
Quote Handling: Supports both single and double quoted arguments
Escape Characters: Handles backslashesfor special characters
Whitespacet: Handles multiple spaces and tabs between arguments
Parsing: Character by character parsing using a simple state machine

Process Management Strategy:
Single Commands: Standard fork/exec pattern for execution
Pipeline Execution: Supports multiple processes connected through pipes
File Descriptors: Proper setup and cleanup of pipes to avoid deadlocks
Error Handling: Provides meaningful messages for invalid or missing executables

System Call Usage:
Process Creation: Uses fork() to create child processes
Program Execution: Uses execv() for full paths and execvp() for PATH searches
Inter-Process Communication: Uses pipe() and dup2() for command chaining
Process Synchronization: Uses waitpid() and wait() for proper child process cleanup

Known Deficiencies/Bugs:

- Only supports one argument per command
- No support for redirection operators (>, <, >>)
- No background process support (&)
- Quote handling does not support nesting
- No command history or line editing features

LESSONS LEARNED

System Programming Concepts:
Process Management: Gained deeper understanding of fork/exec model and process lifecycle
Inter-Process Communication: Learned how to create pipelines and manage file descriptors
Environment Variables: Practiced accessing and using environment information
Signal Handling: Learned about process termination and cleanup procedures

Shell Implementation:
Command Parsing: Practiced input tokenization
Pipeline Execution: Learned how to chain processes together
Built-in vs External Commands: Understood the distinction between internal commands and external executables
Error Handling: Found out the importance of providing meaningful feedback for invalid operations

Development Environment:
Makefile Usage: Gained more experience writing Makefiles for multi-source projects
Memory Management: Practiced dynamic memory allocation and cleanup in C++
Debugging: Practiced systematic testing to confirm shell functionality
Code Organization: Learned how to structure code using modular design principles

C++ Programming:
String Manipulation: Practiced parsing and handling strings for command input
Vectors: Practiced using STL vectors for dynamic data management
