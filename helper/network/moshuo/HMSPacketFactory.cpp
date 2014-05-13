#include "HMSPacketFactory.h"

#include "HMSPacket.h"

NS_CC_H_BEGIN

HPacketBase* HMSPacketFactory::createPacket(const char *buf, size_t len) {
    auto packet = new HMSPacket();
    packet->init();
    packet->autorelease();
    
    uint16_t cmd = ntohs(*(uint16_t*)(buf));
    packet->setCmdKey(cmd);
    packet->beginRead(buf + 2, len - 2);
    return packet;
}

NS_CC_H_END
