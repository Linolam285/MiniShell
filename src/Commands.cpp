#include "Commands.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>

Commands Commands::parseCommand(const std::string& comm, Shell& shell) {
    /*
    Objective: 
    Determine the type of the command
    The args for that type of command
    THe options
    Return the command object
    */

    std::istringstream stream {comm};
    std::string arg {};
    std::vector<std::string> args{};
    std::vector<std::string> options{};
    std::vector<std::string> operators{};
    std::regex r("([><|])|(>>)");

    while (stream >> arg) {
        if (arg.find("-") != std::string::npos) {
            options.emplace_back(arg);
        } else if (std::regex_search(arg,r)) {
            operators.emplace_back(arg);
        } else {
            args.emplace_back(arg);
        }
    }

    if (options.empty() && args.size() == 1 && operators.empty()) {
        return Commands{args[0], shell};
    }
    if (options.empty() && args.size() == 2 && operators.empty()) {
        return Commands{args[0], args, options, shell};
    }
    
    if (!operators.empty()) {
        return Commands{args[0], args, options, operators, shell};
    }


    std::cout << args[0];

    
    return Commands{shell};
}

void Commands::executeCommand() {
    auto it = commandsH.find(m_command_name);
    if (it != commandsH.end()) {
        it->second();
    } else {
        auto it = commandsH.find("exit");
        if (it != commandsH.end()) {
            commandsH["exit"]();
        } else {
            m_shell.setRunning(false);
            std::cerr << "FUNCTION NOT FOUND";
        }
    }
}


