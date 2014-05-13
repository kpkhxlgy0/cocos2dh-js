#include "HBFPacketFactory.h"

#include "HBFPacket.h"

NS_CC_H_BEGIN

HPacketBase* HBFPacketFactory::createPacket(const char *buf, size_t len) {
    auto packet = new HBFPacket();
    packet->init();
    packet->autorelease();

    packet->beginRead(buf, len);
    return packet;
}

NS_CC_H_END
