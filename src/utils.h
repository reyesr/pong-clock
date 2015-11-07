#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <string>

typedef unsigned long long int  MILLIS;

class Utils
{
public:
    static MILLIS now();
    static std::string basedir(const std::string& path);
    static std::string joinPaths(const std::string &path1, const std::string &path2);
};

#endif // TIMEUTILS_H
