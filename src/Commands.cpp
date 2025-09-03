#include "Commands.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>

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
        return Commands{args[0], args, shell};
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

std::vector<const char*> Commands::svToChar(std::vector<std::string> v) {
    std::vector<const char*> argv;
    for (auto& s: v) {
        argv.push_back(const_cast<char*>(s.c_str()));
    }
    argv.push_back(nullptr);
    return argv;
}

void Commands::executeCommand() {
    if (isExternal()) {
        std::cout << "COMMAND NAME : " << m_command_name << "\n";
        std::cout << "M_ARGS[0] : " << m_args[0] << "\n";
        
        if ((m_command_name == "cat") && m_args.size() < 2) {
            std::cout << "Error: missing arguments\n";
            return;
        }

        pid_t pid = fork();
        if (pid == -1) {
            std::cerr << "Error: fork failed\n";
            return;
        }

        if (pid == 0) {
            chdir(m_shell.getPwd().c_str());
            std::vector<const char*> argv = svToChar(m_args);
            execvp(argv[0], const_cast<char* const*>(argv.data()));
            std::cerr << "Error: Execvp failed\n";
            _exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
        return;


    }
    auto it = commandsH.find(m_command_name);
    if (it != commandsH.end()) {
        it->second();
    } else {
        std::cout << "FUNCTION NOT FOUND\n";
    }
}


