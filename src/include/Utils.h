#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <string>

class Utils {
public:
    static const std::vector<std::string> str_explode(const std::string& str, const char& separator);
    static bool str_is_integer(const std::string &str);
    static int call_and_wait(char *argv[]);
};

#endif /* _UTILS_H_ */