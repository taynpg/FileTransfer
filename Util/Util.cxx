#include "Util.h"

#include <filesystem>
namespace fs = std::filesystem;

UtilRet Util::GetHomeDir(std::string& home)
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
    home = homedir;
    return r;
#else
    char* value = nullptr;
    size_t len = 0;
    errno_t err = _dupenv_s(&value, &len, "USERPROFILE");
    if (err != 0 || value == nullptr) {
        r.errMsg = "getenv(USERPROFILE) failed";
        r.ret = false;
        return r;
    }
    r.ret = true;
    home = value;
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
    home = homedir;
    return r;
#endif
}

UtilRet Util::GetDirFile(const std::string& dir, DirFileInfoVec& info)
{
    UtilRet r;

    if (dir.empty() || !fs::exists(dir) || !fs::is_directory(dir)) {
        r.errMsg = "dir is empty or not exist or not a directory";
        r.ret = false;
        return r;
    }

    info.vec.clear();
    try {
        for (auto& p : fs::directory_iterator(dir)) {
            DirFileInfo df;
            df.name = p.path().filename().string();
            df.size = fs::file_size(p.path());
            if (fs::is_directory(p.path())) {
                df.type = Dir;
            } else if (fs::is_regular_file(p.path())) {
                df.type = File;
            } else {
                df.type = Other;
            }
            df.fullPath = p.path().string();
            info.vec.push_back(df);
        }
    } catch (const std::exception& e) {
        r.errMsg = e.what();
        r.ret = false;
        return r;
    }
    r.ret = true;
    return r;
}
