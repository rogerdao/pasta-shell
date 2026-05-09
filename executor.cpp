/*
 * xxxxx yyyyy, xxxxx yyyyy
 * cssc1416, cssc1420
 * CS 480, Summer 2025
 * Assignment #2, Experimental Shell: "XSH"
 * Filename: executor.cpp
 */

#include "shell.h"

/**
 * Execute commands with optional piping - keeping your original structure but simplified
 */
void execute_commands(const std::vector<std::string>& command_parts) {
    int num_cmds = command_parts.size();
    
    // Handle single command (no pipes)
    if (num_cmds == 1) {
        std::vector<char*> args = tokenize(command_parts[0]);
        
        // Check if command is executable
        if (args.empty() || !is_executable(args[0])) {
            if (!args.empty()) {
                std::cout << "xsh: " << args[0] << ": command not found" << std::endl;
            }
            free_tokens(args);
            return;
        }
        
        // Fork and execute single command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            free_tokens(args);
            return;
        }
        
        if (pid == 0) {
            // Child process - execute the command
            if (args[0][0] == '/') {
                execv(args[0], args.data());  // Full path
            } else {
                execvp(args[0], args.data()); // Search PATH
            }
            perror("exec");
            exit(1);
        } else {
            // Parent process - wait for child
            int status;
            waitpid(pid, &status, 0);
        }
        
        free_tokens(args);
        return;
    }
    
    // Handle multiple commands with pipes
    int in_fd = 0;      // Input file descriptor
    int pipefd[2];      // Pipe file descriptors
    pid_t pid;
    
    for (int i = 0; i < num_cmds; ++i) {
        std::vector<char*> args = tokenize(command_parts[i]);
        
        // Check if command is executable
        if (args.empty() || !is_executable(args[0])) {
            if (!args.empty()) {
                std::cout << "xsh: " << args[0] << ": command not found" << std::endl;
            }
            free_tokens(args);
            continue;
        }
        
        // Create pipe for all but the last command
        if (i < num_cmds - 1) {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                free_tokens(args);
                return;
            }
        }
        
        // Fork new process for this command
        pid = fork();
        if (pid == -1) {
            perror("fork");
            free_tokens(args);
            return;
        }
        
        if (pid == 0) {
            // Child process
            
            // Connect input from previous command (if not first)
            if (i > 0) {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            
            // Connect output to next command (if not last)
            if (i < num_cmds - 1) {
                close(pipefd[0]);  // Close read end
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);  // Close write end
            }
            
            // Execute the command
            if (args[0][0] == '/') {
                execv(args[0], args.data());   // Full path
            } else {
                execvp(args[0], args.data());  // Search PATH
            }
            perror("exec");
            exit(1);
        }
        
        // Parent process cleanup
        if (i > 0) {
            close(in_fd);  // Close previous input
        }
        
        if (i < num_cmds - 1) {
            close(pipefd[1]);  // Close write end
            in_fd = pipefd[0]; // Save read end for next command
        }
        
        free_tokens(args);
    }
    
    // Wait for all child processes to complete
    for (int i = 0; i < num_cmds; ++i) {
        wait(nullptr);
    }
}
