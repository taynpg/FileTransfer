#ifndef UTIL_H
#define UTIL_H

#include <InfoDirFile.hpp>
#include <functional>

struct UtilRet {
    bool ret;
    std::wstring errMsg;
};

class Util
{
public:
    static UtilRet GetHomeDir(std::wstring& home);
    static UtilRet GetDirFile(const std::wstring& dir, DirFileInfoVec& info);
    static std::string w2s(const std::wstring& str);
    static std::wstring s2w(const std::string& str);
    static std::string a2u(const std::string& str);
};

class DirFileHelper
{
public:
    DirFileHelper() = default;
    virtual ~DirFileHelper() = default;

public:
    void registerPathCall(const std::function<void(const std::wstring& path)>& call);
    void registerFileCall(const std::function<void(const DirFileInfoVec& vec)>& call);

protected:
    std::function<void(const std::wstring& path)> pathCall_;
    std::function<void(const DirFileInfoVec& info)> infoCall_;

public:
    virtual bool GetHome() = 0;
    virtual bool GetDirFile(const std::wstring& dir) = 0;
};

#endif   // UTIL_H