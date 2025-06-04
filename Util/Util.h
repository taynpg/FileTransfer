#ifndef UTIL_H
#define UTIL_H

#include <InfoDirFile.hpp>
#include <functional>

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

class DirFileHelper
{
public:
    DirFileHelper() = default;
    virtual ~DirFileHelper() = default;

protected:
    std::function<void(const std::string& path)> pathCall_;
    std::function<void(const DirFileInfoVec& info)> infoCall_;

public:
    virtual bool GetHome() = 0;
    virtual bool GetDirFile(const std::string& dir) = 0;
};

#endif   // UTIL_H