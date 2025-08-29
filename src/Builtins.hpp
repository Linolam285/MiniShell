#include "Shell.hpp"

#include <string>


#ifndef BUILTINS_H
#define BUILTINS_H

class Builtins 
{
    public:
        static void exit(Shell& shell, std::string exitCode = "0");
        static void echo(std::string& message);
        static void pwd(Shell& shell);
        static void help();
        static void cd(Shell& shell, std::string& dir);
    private:



};










#endif
