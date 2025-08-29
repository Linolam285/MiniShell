#include <string>

#ifndef SHELL_H
#define SHELL_H

class Shell 
{
    public:

        Shell():
            m_exit_code {0},
            m_running {true},
            m_pwd {} {

            }

        int getExitCode() const {return m_exit_code;}
        bool getRunning() const {return m_running;}
        std::string getPwd() const {return m_pwd;}
        void setPwd(const std::string& new_pwd) {m_pwd = new_pwd;}
        void setExitCode(int exit) {m_exit_code = exit;}
        void setRunning(bool run) {m_running = run;}
        
    private:
        int m_exit_code {};
        bool m_running;
        std::string m_pwd;
};








#endif
