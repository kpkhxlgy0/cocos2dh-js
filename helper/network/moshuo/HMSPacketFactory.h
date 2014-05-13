#ifndef __HELPER_NETWORK_MOSHUO_HMSPACKETFACTORY_H__
#define __HELPER_NETWORK_MOSHUO_HMSPACKETFACTORY_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

#include "../HSocketInterface.h"

NS_CC_H_BEGIN

class HMSPacketFactory : public HPacketFactoryBase {
public:
    virtual HPacketBase* createPacket(const char *buf, size_t len) override;
};

NS_CC_H_END

#endif // __HELPER_NETWORK_MOSHUO_HMSPACKETFACTORY_H__
