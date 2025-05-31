#include "Protocol.h"

#include <algorithm>
#include <cstring>

constexpr unsigned char gHeader[] = {0xFF, 0xFE};
constexpr unsigned char gTail[] = {0xFF, 0xFF};

void MutBuffer::Push(const char* data, int len)
{
    buffer_.insert(buffer_.end(), data, data + len);
}

int MutBuffer::IndexOf(const char* data, int len, int start_pos)
{
    if (start_pos < 0 || start_pos >= static_cast<int>(buffer_.size()) || len <= 0) {
        return -1;
    }
    auto it = std::search(buffer_.begin() + start_pos, buffer_.end(), data, data + len);
    if (it != buffer_.end()) {
        return std::distance(buffer_.begin(), it);
    }
    return -1;
}

int MutBuffer::Length() const
{
    return static_cast<int>(buffer_.size());
}

void MutBuffer::RemoveOf(int start_pos, int len)
{
    if (start_pos < 0 || start_pos >= static_cast<int>(buffer_.size()) || len <= 0) {
        return;
    }
    auto end_pos = std::min(start_pos + len, static_cast<int>(buffer_.size()));
    buffer_.erase(buffer_.begin() + start_pos, buffer_.begin() + end_pos);
}

void MutBuffer::Clear()
{
    buffer_.clear();
}
const char* MutBuffer::GetData() const
{
    return buffer_.data();
}

Protocol::Protocol()
{
}

/*
【 tcp protocol 】
    header      2 char: 0xFF 0xFE
    dataType    2 char;
    from        32 char:
    to          32 char:
    len         4 char:
    data        xxxxx:
    tail        2 char: 0xFF 0xFF
 */
FrameBuffer* Protocol::ParseBuffer(MutBuffer& buffer)
{
    FrameBuffer* frame = nullptr;

    int find = buffer.IndexOf((const char*)gHeader, sizeof(gHeader));
    if (find < 0) {
        return frame;
    }

    int32_t dataLen = 0;
    std::memcpy(&dataLen, buffer.GetData() + find + sizeof(gHeader) + sizeof(uint16_t) + 64, sizeof(dataLen));
    if (buffer.Length() < (find + sizeof(gHeader) + sizeof(uint16_t) + 64 + dataLen + sizeof(dataLen) + sizeof(gTail)) ||
        dataLen < 0) {
        return frame;
    }

    if (std::memcmp(buffer.GetData() + find + sizeof(gHeader) + sizeof(uint16_t) + 64 + sizeof(dataLen) + dataLen, gTail,
                    sizeof(gTail)) != 0) {
        return frame;
    }

    frame = new FrameBuffer();
    frame->len = dataLen;
    frame->fid = std::string(buffer.GetData() + find + sizeof(gHeader) + sizeof(uint16_t));
    frame->tid = std::string(buffer.GetData() + find + sizeof(gHeader) + sizeof(uint16_t) + 32);
    std::memcpy(&frame->dataType, buffer.GetData() + find + sizeof(gHeader), sizeof(frame->dataType));

    if (frame->len > 0) {
        frame->data = new char[frame->len];
        std::memcpy(frame->data, buffer.GetData() + find + sizeof(gHeader) + sizeof(uint16_t) + 64 + sizeof(frame->len),
                    frame->len);
    }
    buffer.RemoveOf(0, find + sizeof(gHeader) + sizeof(uint16_t) + 64 + frame->len + sizeof(frame->len) + sizeof(gTail));
    return frame;
}

bool Protocol::PackBuffer(FrameBuffer* frame, char** buf, int32_t& len)
{
    if (frame == nullptr) {
        return false;
    }
    if (frame->data == nullptr) {
        frame->len = 0;
    }
    len = sizeof(gHeader) + sizeof(uint16_t) + 64 + sizeof(len) + frame->len + sizeof(gTail);
    *buf = new char[len];
    std::memset(*buf + sizeof(gHeader) + sizeof(uint16_t), 0x0, 64);
    std::memcpy(*buf, gHeader, sizeof(gHeader));
    std::memcpy(*buf + sizeof(gHeader), &frame->dataType, sizeof(frame->dataType));
    std::memcpy(*buf + sizeof(gHeader) + sizeof(uint16_t), frame->fid.c_str(), frame->fid.size());
    std::memcpy(*buf + sizeof(gHeader) + sizeof(uint16_t) + 32, frame->tid.c_str(), frame->tid.size());
    std::memcpy(*buf + sizeof(gHeader) + sizeof(uint16_t) + 64, &frame->len, sizeof(frame->len));
    if (frame->len > 0) {
        std::memcpy(*buf + sizeof(gHeader) + sizeof(uint16_t) + 64 + sizeof(len), frame->data, frame->len);
    }
    std::memcpy(*buf + sizeof(gHeader) + sizeof(uint16_t) + 64 + sizeof(len) + frame->len, gTail, sizeof(gTail));
    frame->data = nullptr;
    return true;
}

FrameBuffer::FrameBuffer()
{
}

FrameBuffer::~FrameBuffer()
{
    delete[] data;
    len = 0;
}
