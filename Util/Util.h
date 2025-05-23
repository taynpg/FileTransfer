#ifndef UTIL_H
#define UTIL_H

#include <InfoDirFile.hpp>

struct UtilRet {
    bool ret;
    std::string errMsg;
};

class Util
{
public:
    static UtilRet GetHomeDir(std::string& home);
    static UtilRet GetDirFile(const std::string& dir, DirFileInfoVec& info);
    static std::string STLWhat(const std::exception& e);
};

#endif   // UTIL_H