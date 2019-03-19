#include <Utils.h>

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