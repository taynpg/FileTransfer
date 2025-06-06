#include "Util.h"

#include <filesystem>
#include <utf8.h>
namespace fs = std::filesystem;

#ifdef _WIN32
#include <windows.h>
std::string u8_to_ansi(const std::string& str)
{
    int wideCharLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    if (wideCharLen <= 0) {
        return "";
    }
    std::wstring wideStr(wideCharLen, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wideStr[0], wideCharLen);
    int gbkLen = WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (gbkLen <= 0) {
        return "";
    }
    std::string gbkStr(gbkLen, '\0');
    WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, &gbkStr[0], gbkLen, nullptr, nullptr);

    gbkStr.resize(gbkLen - 1);
    return gbkStr;
}
std::string ansi_to_u8(const std::string& str)
{
    int wideCharLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    if (wideCharLen <= 0) {
        return "";
    }
    std::wstring wideStr(wideCharLen, L'\0');
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wideStr[0], wideCharLen);

    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8Len <= 0) {
        return "";
    }
    std::string utf8Str(utf8Len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &utf8Str[0], utf8Len, nullptr, nullptr);

    utf8Str.resize(utf8Len - 1);
    return utf8Str;
}
#endif

UtilRet Util::GetHomeDir(std::wstring& home)
{
    UtilRet r;
#ifdef _WIN32
#if defined(__MINGW32__) || defined(__MINGW64__)
    auto* homedir = getenv("USERPROFILE");
    if (homedir == nullptr) {
        r.errMsg = "getenv(USERPROFILE) failed";
        r.ret = false;
        return r;
    }
    r.ret = true;
    home = Util::s2w(homedir);
    return r;
#else
    char* value = nullptr;
    size_t len = 0;
    errno_t err = _dupenv_s(&value, &len, "USERPROFILE");
    if (err != 0 || value == nullptr) {
        r.errMsg = L"getenv(USERPROFILE) failed";
        r.ret = false;
        return r;
    }
    r.ret = true;
    home = Util::s2w(value);
    free(value);
    return r;
#endif
#else
    char* homedir = getenv("HOME");
    if (homedir == nullptr) {
        r.errMsg = "getenv(HOME) failed";
        r.ret = false;
        return r;
    }
    r.ret = true;
    home = Util::s2w(homedir);
    return r;
#endif
}

UtilRet Util::GetDirFile(const std::wstring& dir, DirFileInfoVec& info)
{
    UtilRet r;

    if (dir.empty() || !fs::exists(dir) || !fs::is_directory(dir)) {
        r.errMsg = L"dir is empty or not exist or not a directory";
        r.ret = false;
        return r;
    }

    info.vec.clear();
    try {
        for (auto& p : fs::directory_iterator(dir)) {
            DirFileInfo df;
            df.name = p.path().filename().wstring();
            df.size = fs::file_size(p.path());
            if (fs::is_directory(p.path())) {
                df.type = Dir;
            } else if (fs::is_regular_file(p.path())) {
                df.type = File;
            } else {
                df.type = Other;
            }
            df.fullPath = p.path().wstring();
            info.vec.push_back(df);
        }
    } catch (const std::exception& e) {
        r.errMsg = Util::s2w(e.what());
        r.ret = false;
        return r;
    }
    r.ret = true;
    return r;
}

std::string Util::w2s(const std::wstring& str)
{
    std::string utf8_result;
    try {
        utf8::utf16to8(str.begin(), str.end(), std::back_inserter(utf8_result));
    } catch (const std::exception& e) {
        return "";
    }
    return utf8_result;
}

std::wstring Util::s2w(const std::string& str)
{
    std::wstring wide_result;
    try {
        utf8::utf8to16(str.begin(), str.end(), std::back_inserter(wide_result));
    } catch (const std::exception& e) {
        return L"";
    }
    return wide_result;
}

std::string Util::a2u(const std::string& str)
{
#ifdef _WIN32
    return ansi_to_u8(str);
#else
    return str;
#endif
}

void DirFileHelper::registerPathCall(const std::function<void(const std::wstring& path)>& call)
{
    pathCall_ = call;
}
void DirFileHelper::registerFileCall(const std::function<void(const DirFileInfoVec& vec)>& call)
{
    infoCall_ = call;
}