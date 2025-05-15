#ifndef INFOENHANCE_HPP
#define INFOENHANCE_HPP

#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <streambuf>

class ZeroCopyInput
{
public:
    ZeroCopyInput(const char* data, size_t size)
        : streamBuf_(data, size), stream_(&streamBuf_)
    {
    }
    cereal::BinaryInputArchive archive()
    {
        return cereal::BinaryInputArchive(stream_);
    }

private:
    class ConstStreamBuf : public std::streambuf
    {
    public:
        ConstStreamBuf(const char* data, size_t size)
        {
            setg(const_cast<char*>(data), const_cast<char*>(data),
                 const_cast<char*>(data + size));
        }
    };

    ConstStreamBuf streamBuf_;
    std::istream stream_;
};

#endif   // INFOENHANCE_HPP