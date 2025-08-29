#include "Builtins.hpp"
#include "Shell.hpp"


#include <string>
#include <iostream>

void Builtins::exit(Shell& shell, std::string exitCode = "0") {
    shell.setExitCode(std::stoi(exitCode));
    shell.setRunning(false);
}

void Builtins::echo(std::string& message) {
    std::cout << message;
}

void Builtins::pwd(Shell& shell) {
    std::cout << shell.getPwd();
}

void Builtins::help() {
    std::cout << "exit [code]\n cd <dir>\n pwd\n echo [text]\n help\n";
}

void Builtins::cd(Shell& shell, std::string &dir) {
    shell.setPwd(dir);
}
