#include "Builtins.hpp"
#include "Commands.hpp"
#include "Shell.hpp"
#include "Utils.hpp"

#include <string>
#include <iostream>


int main() {
    Shell shell {};
    while (shell.getRunning()) {
        std::string s_command {};
        std::getline(std::cin, s_command);
        Commands command {Commands::parseCommand(s_command,shell)};
        command.executeCommand();
    }
    return 0;
}
