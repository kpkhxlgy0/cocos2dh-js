#ifndef __HELPER_NETWORK_MOSHUO_HMSPACKET_H__
#define __HELPER_NETWORK_MOSHUO_HMSPACKET_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

#include "../HSocketInterface.h"

namespace msgpack {
    class sbuffer;
    template <typename T> class packer;
    class unpacker;
    class unpacked;
}

NS_CC_H_BEGIN

class HMSPacket : public Ref, public HPacketBase {
public:
    HMSPacket();
    ~HMSPacket();
    bool init();
    
    void beginRead(const char *INbuffer, size_t INsize);
    bool readBool();
    int8_t readInt8();
    uint8_t readUInt8();
    int16_t readInt16();
    uint16_t readUInt16();
    int32_t readInt32();
    uint32_t readUInt32();
    int64_t readInt64();
    uint64_t readUInt64();
    float readFloat();
    double readDouble();
    std::string readString();
    std::string readBuffer();
    
    void beginWrite();
    void writeBool(bool INvalue);
    void writeInt8(char INvalue);
    void writeUInt8(uint8_t INvalue);
    void writeInt16(int16_t INvalue);
    void writeUInt16(uint16_t INvalue);
    void writeInt32(int32_t INvalue);
    void writeUInt32(uint32_t INvalue);
    void writeInt64(int64_t INvalue);
    void writeUInt64(uint64_t INvalue);
    void writeFloat(float INvalue);
    void writeDouble(double INvalue);
    void writeString(const std::string &INvalue);
    void writeBuffer(const char *INvalue, size_t INlen);
    
    void setRoute(uint32_t route);
    uint32_t getRoute() const;
    void setCmdKey(uint16_t cmdKey);
    uint16_t getCmdKey() const;
    
    const char* getBuffer() override;
    size_t getLength() override;
public:
    static HMSPacket* create();
private:
    msgpack::sbuffer *m_buffer;
    msgpack::packer<msgpack::sbuffer> *m_packer;
    msgpack::unpacker *m_unpacker;
    msgpack::unpacked *m_unpacked;
    uint32_t _route;
    uint16_t _cmdKey;
    char *_bufToSend;
};

NS_CC_H_END

#endif //__HELPER_NETWORK_MOSHUO_HMSPACKET_H__
