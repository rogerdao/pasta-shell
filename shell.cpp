#include "shell.h"

void init() {
    std::cout << "Welcome to XSH (Experimental Shell)!" << std::endl;
}

void cleanup() {
    std::cout << "Shell exiting. Goodbye!" << std::endl;
}

void loop() {
    std::string input;

    while (true) {
        std::cout << "cssc0000% ";
        std::getline(std::cin, input);

        if (input == "exit") break;
        if (input.empty()) continue;

        std::vector<std::string> parts = split(input, '|');
        execute_commands(parts);
    }
}

std::vector<std::string> split(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string part;

    while (std::getline(ss, part, delimiter)) {
        tokens.push_back(part);
    }

    return tokens;
}

std::vector<char*> tokenize(const std::string& command_line) {
    std::vector<char*> args;
    std::stringstream ss(command_line);
    std::string token;

    while (ss >> token) {
        char* arg = new char[token.size() + 1];
        std::strcpy(arg, token.c_str());
        args.push_back(arg);
    }

    args.push_back(nullptr); // Required by execvp
    return args;
}

bool is_executable(const char* /* path */) {
    // Checks if the file exists and is executable in the current directory/exact path
    // return access(path, X_OK) == 0;
    // Let execvp handle the PATH searching and error reporting	
    // comment out path
    return true;
}

void free_tokens(std::vector<char*>& tokens) {
    // Frees the dynamically allocated memory from the tokenize() function
    for (char* token : tokens) {
        if (token != nullptr) {
            delete[] token;
        }
    }
    tokens.clear();
}
