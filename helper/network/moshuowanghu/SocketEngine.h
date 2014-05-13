/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   xxxx
 @History       (操作 -- 创建)(时间 -- 13-2-26)
 */

#ifndef __COCOS2DXMOSHUO_CLASSES_SOCKETENGINE_H__
#define __COCOS2DXMOSHUO_CLASSES_SOCKETENGINE_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

#include "HSocketClient.h"

#define MAKE_LONG(a, b)	((int32_t)(((int16_t)(((intptr_t)(a)) & 0xffff)) | \
((int32_t)((int16_t)(((intptr_t)(b)) & 0xffff))) << 16))

NS_CC_H_BEGIN

class SocketEngine {
public:
    SocketEngine();
    int getHeadLength();
    int checkFinished(cocos2d::h::HSocketPacket *INpacket);
    void encode(cocos2d::h::HSocketPacket *INpacket);
    void decode(cocos2d::h::HSocketPacket *INpacket);
    uint16_t EncryptBuffer(uint8_t pcbDataBuffer[], uint16_t wDataSize, uint16_t wBufferSize);
    uint16_t CrevasseBuffer(uint8_t pcbDataBuffer[], uint16_t wDataSize);
    inline uint16_t SeedRandMap(uint16_t wSeed);
    inline uint8_t MapSendByte(uint8_t const cbData);
    inline uint8_t MapRecvByte(uint8_t const cbData);
private:
    uint8_t							m_cbSendRound;
    uint8_t							m_cbRecvRound;
    uint32_t						m_dwSendXorKey;
    uint32_t						m_dwRecvXorKey;
    
    uint32_t						m_dwSendTickCount;
    uint32_t						m_dwRecvTickCount;
    uint32_t						m_dwSendPacketCount;
    uint32_t						m_dwRecvPacketCount;
};

NS_CC_H_END

#endif // __COCOS2DXMOSHUO_CLASSES_SOCKETENGINE_H__
