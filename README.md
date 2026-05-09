CS 480, Experimental Shell

Collaborators:
xxxxx yyyyy - cssc1416  
xxxxx yyyyy - cssc1420

DESCRIPTION

This program implements XSH (Experimental Shell), a minimal Unix shell that provides basic command execution and piping functionality.

Requirements:
- Needs a POSIX-compliant system with fork(), exec(), and pipe() support

COMPILATION INSTRUCTIONS

1. Clean up any pre-generated files using `"make clean"`
2. Compile the project using the `make` command
3. The executable "`dsh`" will then be created in the current directory

OPERATING INSTRUCTIONS

Quick-Start:
- Run the program with ./dsh
- Exit with "exit"
- Requires POSIX-compliant system (use WSL if running Windows)

Valid Input Formats:
- username% executablefilename
- username% executablefilename argument (only one argument)
- username% executablefilename | executablefilename
- username% executablefilename | executablefilename | executablefilename (any number of pipes)
- username% exit

DESIGN DECISIONS

System Call Usage:  
Process Creation: Uses fork() to create child processes  
Program Execution: Uses execv() for full paths and execvp() for PATH searches  
Inter-Process Communication: Uses pipe() and dup2() for command chaining  
Process Synchronization: Uses waitpid() and wait() for proper child process cleanup

Process Management Strategy:  
Single Commands: Standard fork/exec pattern for execution  
Error Handling: Provides messages for invalid or missing executables  
Pipeline Execution: Multiple processes are connected through pipes  
File Descriptors: Setup and cleanup of pipes to avoid deadlocks

Tokenizing/Parsing:  
Parsing: Character by character parsing using a simple state machine  
Whitespaces: Handles multiple spaces and tabs between arguments  
Quote Handling: Supports both single and double quoted arguments  
Escape Characters: Handles backslashes for special characters

Environment Variable Integration:  
Fallback Strategy: Defaults to "cssc0000%" if no environment variables are found  
Username Detection: Checks USER environment variable first, then LOGNAME as fallback if needed

Output:  
Command execution output displayed to terminal  
Error messages for invalid or non-existent commands

Code Architecture:  
Focused Tasks: Parsing, execution, and environment handling separated into dedicated functions  
Modular Design: Main function kept short as a list of function calls

Known Deficiencies/Bugs:

- Only supports one argument per command
- No support for redirection operators (>, <, >>)
- No background process support (&)
- No command history or line editing features
