#include <Utils.h>
#include <unistd.h>
#include <sys/wait.h>

const std::vector<std::string> Utils::str_explode(const std::string& str, const char& separator)
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

bool Utils::str_is_integer(const std::string &str)
{
    if(str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+')))
        return false;

    char * p ;
    strtol(str.c_str(), &p, 10) ;

    return (*p == 0);
}

int Utils::call_and_wait(char *argv[])
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