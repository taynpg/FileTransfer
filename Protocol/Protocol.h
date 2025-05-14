#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <vector>
#include <string>
#include <cstdint>

// It is specified here that the first 30 contents (inclusive) are
// used for communication with the server.
// Contents beyond 30 are only forwarded.
enum FrameBufferType : uint16_t {
    FBT_SER_MSG_ASKCLIENTS = 0,
    FBT_SER_MSG_YOURID,
    FBT_SER_MSG_RESPONSE,
    FBT_CLI_BIN_FILEDATA = 31,
    FBT_CLI_MSG_COMMUNICATE,
    FBT_CLI_ASK_DIRFILE,
    FBT_CLI_ANS_DIRFILE,
    FBT_CLI_ASK_HOME,
    FBT_CLI_ANS_HOME
};

struct FrameBuffer {
    FrameBuffer();
    ~FrameBuffer();

    int32_t len{};
    char* dataMut;
    std::string fid;
    std::string tid;
    const char* dataConst;
    FrameBufferType dataType{};
};

class MutBuffer
{
public:
    MutBuffer() = default;

public:
    void Push(const char* data, int len);
    int IndexOf(const char* data, int len, int start_pos = 0);
    const char* GetData() const;
    int Length() const;
    void RemoveOf(int start_pos, int len);
    void Clear();

private:
    std::vector<char> buffer_;
};

class Protocol
{
public:
    Protocol();

public:
    static FrameBuffer* ParseBuffer(MutBuffer& buffer);
    static bool PackBuffer(FrameBuffer* frame, char** buf, int32_t& len);
};

#endif // PROTOCOL_H
