#ifndef LOCALFILE_H
#define LOCALFILE_H

#include <globalDefine.h>

#include "Util.h"

class LocalFile : public DirFileHelper
{
public:
    LocalFile() = default;
    ~LocalFile() override = default;

public:
    std::wstring GetErr() const;
    bool GetHome() override;
    bool GetDirFile(const std::wstring& dir) override;

private:
    std::wstring err_;
};

#endif   // LOCALFILE_H