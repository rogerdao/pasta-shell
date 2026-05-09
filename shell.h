#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

// Shell lifecycle
void init();               // Optional setup at start
void loop();               // Main shell loop
void cleanup();            // Optional cleanup at end

// Core functions
void execute_commands(const std::vector<std::string>& commands);
std::vector<std::string> split(const std::string& input, char delimiter);
std::vector<char*> tokenize(const std::string& command_line);

bool is_executable(const char* path);
void free_tokens(std::vector<char*>& tokens);

#endif
