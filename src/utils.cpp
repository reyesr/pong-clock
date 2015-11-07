#include "utils.h"
#include <chrono>

MILLIS Utils::now()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string Utils::basedir(const std::string &path)
{
    auto last = path.find_last_of("/");
    if (last != std::string::npos) {
        return path.substr(0, last);
    }
    return path;
}

std::string Utils::joinPaths(const std::string &path1, const std::string &path2)
{
    if (path1.size() == 0) {
        return path2;
    }
    if (path2.size() == 0) {
        return path1;
    }

    std::string path = path1;
    if (path1.back() != '/') {
        path += '/';
    }
    path += path2.back()=='/' ? path2.substr(1) : path2;
    return path;

}
