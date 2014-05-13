#ifndef __HELPER_NETWORK_BF_HBFPACKET_H__
#define __HELPER_NETWORK_BF_HBFPACKET_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

#include "../HSocketInterface.h"

NS_CC_H_BEGIN

class HBFPacket : public Ref, public HPacketBase {
public:
    HBFPacket();
    ~HBFPacket();
    bool init();
    
    void beginRead(const char *buffer, size_t size);
    std::string readString();
    
    void beginWrite();
    void writeString(const std::string &value);
    
    const char* getBuffer() override;
    size_t getLength() override;
public:
    static HBFPacket* create();
private:
    std::vector<char> _buffer;
    char *_bufToSend;
};

NS_CC_H_END

#endif //__HELPER_NETWORK_BF_HBFPACKET_H__
