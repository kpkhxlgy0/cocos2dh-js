#ifndef __HELPER_NETWORK_HSOCKETINTERFACE_H__
#define __HELPER_NETWORK_HSOCKETINTERFACE_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

#define MAX_BUFFER_LENGTH 4096

static bool isBigEndian() {
    const int16_t n = 1;
    if(*(int8_t*)&n)  {
        return false;
    }
    return true;
}

static uint64_t swap_64(uint64_t num) {
	return ((num >> 56) |
            ((num & 0x00ff000000000000) >> 40) |
            ((num & 0x0000ff0000000000) >> 24) |
            ((num & 0x000000ff00000000) >> 8)  |
            ((num & 0x00000000ff000000) << 8)  |
            ((num & 0x0000000000ff0000) << 24) |
            ((num & 0x000000000000ff00) << 40) |
            ((num << 56)));
}

#ifndef htonll
#define htonll(ll) isBigEndian() ? ll : swap_64(ll)
#endif // htonll

#ifndef ntohll
#define ntohll(ll) isBigEndian() ? ll : swap_64(ll)
#endif // ntohll

class HPacketBase {
public:
    virtual const char* getBuffer() = 0;
    virtual size_t getLength() = 0;
};

class HPacketFactoryBase {
public:
    virtual HPacketBase* createPacket(const char *buf, size_t len) = 0;
};

class HSocketDelegateBase {
public:
    virtual void callbackConnected() = 0;
    virtual void callbackConnectFailed() = 0;
    virtual void callbackDisconnected() = 0;
    virtual void callbackReceived(HPacketBase *INpacket) = 0;
};

NS_CC_H_END

#endif // __HELPER_NETWORK_HSOCKETINTERFACE_H__
