#include "LocalFile.h"

#include <chrono>
#include <filesystem>
#include <string>

#include "Util.h"

namespace fs = std::filesystem;

std::wstring LocalFile::GetErr() const
{
    return err_;
}

bool LocalFile::GetHome()
{
    std::wstring home;
    auto r = Util::GetHomeDir(home);
    if (!r.ret) {
        err_ = r.errMsg;
        return false;
    }
    pathCall_(home);
    return true;
}

bool LocalFile::GetDirFile(const std::wstring& dir)
{
    DirFileInfoVec vec;
    fs::path path(dir);
    if (!fs::exists(path) || !fs::is_directory(path)) {
        err_ = tr(L"Path is not a directory or does not exist");
        return false;
    }
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            DirFileInfo info;
            const auto& p = entry.path();
            info.fullPath = p.wstring();
            info.name = p.filename().wstring();
            if (entry.is_directory()) {
                info.type = Dir;
                info.size = 0;
            } else if (entry.is_regular_file()) {
                info.type = File;
                info.size = entry.file_size();
            } else {
                continue;
            }
            // auto lwt = entry.last_write_time();
            // auto me = lwt.time_since_epoch();
            // auto ms_since_epoch = std::chrono::duration_cast<std::chrono::seconds>(me);
            // info.lastModifyTime = static_cast<uint64_t>(ms_since_epoch.count());

            auto lwt = entry.last_write_time();
            auto sys_time = std::chrono::time_point_cast<std::chrono::system_clock::duration>(lwt - decltype(lwt)::clock::now() +
                                                                                              std::chrono::system_clock::now());
            auto ms_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(sys_time.time_since_epoch());
            info.lastModifyTime = static_cast<uint64_t>(ms_since_epoch.count());
            vec.vec.push_back(info);
        }
    } catch (const std::exception& e) {
        err_ = Util::s2w(e.what());
        return false;
    }
    infoCall_(vec);
    return true;
}
