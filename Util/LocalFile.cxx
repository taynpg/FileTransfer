#include "LocalFile.h"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

std::string LocalFile::GetErr() const
{
    return err_;
}

bool LocalFile::GetHome()
{
#if defined(_WIN32)
// _dupenv_s() was introduced in Visual Studio 2008's CRT (msvcr90) and does not seem to have made it into the system CRT
// (msvcrt). MinGW-w64 GCC typically links only to the system CRT by default, so this symbol cannot be found.
#if defined(__MINGW32__) || defined(__MINGW64__)
    char* homedir = std::getenv("USERPROFILE");
    if (homedir) {
        err_ = tr("get env USERPROFILE failed.");
        std::string home(homedir);
        pathCall_(home);
        return true;
    }
    return false;
#else
    auto err = _dupenv_s(&value, &len, "USERPROFILE");
    if (err == 0 && value != nullptr) {
        std::string ret(value);
        free(value);
        pathCall_(home);
        return true;
    } else {
        err_ = tr("get env USERPROFILE failed.");
        return false;
    }
#endif
#else
    char* homedir = getenv("HOME");
    if (homedir) {
        std::string home(homedir);
        pathCall_(home);
        return true;
    }
    err_ = tr("get env HOME failed.");
    return false;
#endif
}

bool LocalFile::GetDirFile(const std::string& dir)
{
    DirFileInfoVec vec;
    fs::path path(dir);
    if (!fs::exists(path) || !fs::is_directory(path)) {
        err_ = tr("Path is not a directory or does not exist");
        return false;
    }

    try
    {
        for (const auto& entry : fs::directory_iterator(path))
        {
            DirFileInfo info;
            const auto& p = entry.path();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return false;
}
