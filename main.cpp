#include "shell.h"

// The main function outlines the shell's lifecycle:
// 1. init      - perform any startup tasks
// 2. loop      - main REPL (Read-Eval-Print Loop)
// 3. cleanup   - handle shutdown tasks if needed
int main() {
    init();       // Initialize the shell (e.g., welcome message)
    loop();       // Run the shell prompt loop
    cleanup();    // Clean up and exit

    return 0;
}