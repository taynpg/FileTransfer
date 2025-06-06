#ifndef DIRFILE_H
#define DIRFILE_H

#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cstdint>
#include <string>
#include <vector>

enum FileType : uint32_t { None = 0, File, Dir, Link, Other };

struct DirFileInfo {
    std::wstring name;
    uint64_t size = 0;
    FileType type = None;
    std::wstring fullPath;
    uint16_t permission = 0;
    uint64_t lastModifyTime = 0;
    DirFileInfo() = default;
    template <class Archive> void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(name), CEREAL_NVP(size), CEREAL_NVP(type),
                CEREAL_NVP(fullPath), CEREAL_NVP(permission),
                CEREAL_NVP(lastModifyTime));
    }
};

struct DirFileInfoVec {
    std::vector<DirFileInfo> vec;
    template <class Archive> void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(vec));
    }
};

#endif