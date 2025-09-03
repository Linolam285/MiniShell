#include "Builtins.hpp"
#include "Shell.hpp"

#include <unistd.h>
#include <limits.h>
#include <string>
#include <iostream>

void Builtins::exit(Shell& shell, std::string exitCode) {
    shell.setExitCode(std::stoi(exitCode));
    shell.setRunning(false);
}

void Builtins::echo(std::string& message) {
    std::cout << message << "\n";
}

void Builtins::pwd(Shell& shell) {
    char buffer[PATH_MAX];
    if (getcwd(buffer,PATH_MAX) == NULL) {
        std::cout << "ERROR\n";
    }
    std::cout << buffer << "\n";
}

void Builtins::help() {
    std::cout << "exit [code]\n cd <dir>\n pwd\n echo [text]\n help\n";
}

void Builtins::cd(Shell& shell, std::string &dir) {
    if (chdir(dir.c_str()) == 0) {
        shell.setPwd(dir);
    } else {
        std::string message = "Invalid Directory\n";
        Builtins::echo(message);
    }
}
