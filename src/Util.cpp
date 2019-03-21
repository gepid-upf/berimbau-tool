/**
 * @file Util.cpp
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * 
 * @brief A set of utilities to use with C++. Some code are a mix of what was
 * found searching online. The links for reference are with the source code.
 * 
 * @copyright
 * Copyright 2019 Angelo Elias Dalzotto
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <Util.h>
#include <unistd.h>
#include <sys/wait.h>

// http://www.cplusplus.com/articles/2wA0RXSz/
const std::vector<std::string> Util::String::explode(const std::string& str, const char& separator)
{
    std::string buff{""};
    std::vector<std::string> v;

    for(auto n:str)
    {
        if(n != separator) buff+=n; else
        if(n == separator && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

// https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int/2845275#2845275
bool Util::String::is_integer(const std::string &str)
{
    if(str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+')))
        return false;

    char * p;
    strtol(str.c_str(), &p, 10);

    return (*p == 0);
}

int Util::System::call_and_wait(char *argv[])
{
    int pid = fork();
    if(!pid){
        exit(execvp(argv[0], argv));
    } else {
        int status;
        pid = waitpid(pid, &status, 0);

        if(pid < 0)
            return pid; // Wait error
       
        return WEXITSTATUS(status);
    }
}