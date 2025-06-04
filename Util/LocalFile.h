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
    std::string GetErr() const;
    bool GetHome() override;
    bool GetDirFile(const std::string& dir) override;

private:
    std::string err_;
};

#endif   // LOCALFILE_H