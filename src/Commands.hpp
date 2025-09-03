#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <functional>
#include <iostream>

#include "Builtins.hpp"
#include "Shell.hpp"

#ifndef COMMANDS_H
#define COMMANDS_H

class Commands {
    
    public:

        enum CommandNames
        {
            cd,
            pwd,
            ls,
            echo,
            exit,
            cat,
            touch,
            mkdir,
            rmdir,
            rm
        };

    
        std::unordered_map<std::string, std::function<void()>> commandsH;

        Commands(Shell& shell):
            m_command_name {},
            m_args {},
            m_operators {},
            m_options {},
            m_shell {shell} {
                init();
            }
        
        static Commands parseCommand(const std::string& comm, Shell& shell); // parse to get vector of args options operators and command name
        void executeCommand(); //delegates to Builtins etc
        void executeExternalCommand();
        std::vector<const char*> svToChar(std::vector<std::string> v);
        std::string getCommandName() const {return m_command_name;}
        std::vector<std::string> getArgs() const {return m_args;}
        std::vector<std::string> getOptions() const {return m_options;}
        std::vector<std::string> getOperators() const {return m_operators;}
        void init() {
            commandsH["cd"] = [this](){
                if (m_args.size() > 1) {
                    Builtins::cd(m_shell, m_args[1]);
                } else {
                    std::cout << "Usage: cd [dir_name]\n";
                }
            };
            commandsH["pwd"] = [this](){Builtins::pwd(m_shell);};
            commandsH["echo"] = [this](){
                if (m_args.size() > 1) {
                    Builtins::echo(m_args[1]);
                } else {
                    std::cout << "Usage: echo MESSAGE\n";
                }
            };
            commandsH["exit"] = [this](){
                if (m_args.size() > 1) {
                    Builtins::exit(m_shell, m_args[1]);
                } else {
                    std::cout << "Usage: exit [exit_code]\n";
                    Builtins::exit(m_shell, "0");
                }
            };
            commandsH["help"] = [this](){Builtins::help();};
        }
        bool isExternal() {
            std::array<std::string,2> externalCommandsArray = {"ls", "cat"};
            return std::find(externalCommandsArray.begin(), externalCommandsArray.end(), m_command_name) != externalCommandsArray.end();
        }
        
    private:
        const std::string m_command_name;
        std::vector<std::string> m_args {};
        std::vector<std::string> m_options {};
        std::vector<std::string> m_operators {};
        Shell& m_shell;

        Commands(const std::string& command_name, std::vector<std::string> args, Shell& shell):  // pwd, exit, history
            m_command_name {command_name},
            m_args {args},
            m_shell {shell} {
                init();
            }
        
        Commands(const std::string& command_name, std::vector<std::string> args, std::vector<std::string> options, Shell& shell):
            m_command_name {command_name},
            m_args {args},
            m_options {options},
            m_shell {shell} {
                init();
            }
        Commands(const std::string& command_name, std::vector<std::string> args, std::vector<std::string> options, std::vector<std::string> operators, Shell& shell):
            m_command_name {command_name},
            m_args {args},
            m_options {options},
            m_operators {operators},
            m_shell {shell} {
                init();
            }
};








#endif
