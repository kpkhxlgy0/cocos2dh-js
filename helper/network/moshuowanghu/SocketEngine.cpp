/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   xxxx
 @History       (操作 -- 创建)(时间 -- 13-2-26)
 */

#include "SocketEngine.h"

#include "HSocketPacket.h"
#include "../../../helper/native/HNative.h"
#include "../../../helper/crypto/HCrypto.h"
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include <netinet/in.h>
#endif

NS_CC_H_BEGIN

//////////////////////////////////////////////////////////////////////////

// crypto key
const uint32_t g_dwPacketKey = 0xA66AA66A;

// send map
const uint8_t g_SendByteMap[256] =
{
    0x70, 0x2F, 0x40, 0x5F, 0x44, 0x8E, 0x6E, 0x45, 0x7E, 0xAB, 0x2C, 0x1F, 0xB4, 0xAC, 0x9D, 0x91,
    0x0D, 0x36, 0x9B, 0x0B, 0xD4, 0xC4, 0x39, 0x74, 0xBF, 0x23, 0x16, 0x14, 0x06, 0xEB, 0x04, 0x3E,
    0x12, 0x5C, 0x8B, 0xBC, 0x61, 0x63, 0xF6, 0xA5, 0xE1, 0x65, 0xD8, 0xF5, 0x5A, 0x07, 0xF0, 0x13,
    0xF2, 0x20, 0x6B, 0x4A, 0x24, 0x59, 0x89, 0x64, 0xD7, 0x42, 0x6A, 0x5E, 0x3D, 0x0A, 0x77, 0xE0,
    0x80, 0x27, 0xB8, 0xC5, 0x8C, 0x0E, 0xFA, 0x8A, 0xD5, 0x29, 0x56, 0x57, 0x6C, 0x53, 0x67, 0x41,
    0xE8, 0x00, 0x1A, 0xCE, 0x86, 0x83, 0xB0, 0x22, 0x28, 0x4D, 0x3F, 0x26, 0x46, 0x4F, 0x6F, 0x2B,
    0x72, 0x3A, 0xF1, 0x8D, 0x97, 0x95, 0x49, 0x84, 0xE5, 0xE3, 0x79, 0x8F, 0x51, 0x10, 0xA8, 0x82,
    0xC6, 0xDD, 0xFF, 0xFC, 0xE4, 0xCF, 0xB3, 0x09, 0x5D, 0xEA, 0x9C, 0x34, 0xF9, 0x17, 0x9F, 0xDA,
    0x87, 0xF8, 0x15, 0x05, 0x3C, 0xD3, 0xA4, 0x85, 0x2E, 0xFB, 0xEE, 0x47, 0x3B, 0xEF, 0x37, 0x7F,
    0x93, 0xAF, 0x69, 0x0C, 0x71, 0x31, 0xDE, 0x21, 0x75, 0xA0, 0xAA, 0xBA, 0x7C, 0x38, 0x02, 0xB7,
    0x81, 0x01, 0xFD, 0xE7, 0x1D, 0xCC, 0xCD, 0xBD, 0x1B, 0x7A, 0x2A, 0xAD, 0x66, 0xBE, 0x55, 0x33,
    0x03, 0xDB, 0x88, 0xB2, 0x1E, 0x4E, 0xB9, 0xE6, 0xC2, 0xF7, 0xCB, 0x7D, 0xC9, 0x62, 0xC3, 0xA6,
    0xDC, 0xA7, 0x50, 0xB5, 0x4B, 0x94, 0xC0, 0x92, 0x4C, 0x11, 0x5B, 0x78, 0xD9, 0xB1, 0xED, 0x19,
    0xE9, 0xA1, 0x1C, 0xB6, 0x32, 0x99, 0xA3, 0x76, 0x9E, 0x7B, 0x6D, 0x9A, 0x30, 0xD6, 0xA9, 0x25,
    0xC7, 0xAE, 0x96, 0x35, 0xD0, 0xBB, 0xD2, 0xC8, 0xA2, 0x08, 0xF3, 0xD1, 0x73, 0xF4, 0x48, 0x2D,
    0x90, 0xCA, 0xE2, 0x58, 0xC1, 0x18, 0x52, 0xFE, 0xDF, 0x68, 0x98, 0x54, 0xEC, 0x60, 0x43, 0x0F
};

//recv map
const uint8_t g_RecvByteMap[256] =
{
    0x51, 0xA1, 0x9E, 0xB0, 0x1E, 0x83, 0x1C, 0x2D, 0xE9, 0x77, 0x3D, 0x13, 0x93, 0x10, 0x45, 0xFF,
    0x6D, 0xC9, 0x20, 0x2F, 0x1B, 0x82, 0x1A, 0x7D, 0xF5, 0xCF, 0x52, 0xA8, 0xD2, 0xA4, 0xB4, 0x0B,
    0x31, 0x97, 0x57, 0x19, 0x34, 0xDF, 0x5B, 0x41, 0x58, 0x49, 0xAA, 0x5F, 0x0A, 0xEF, 0x88, 0x01,
    0xDC, 0x95, 0xD4, 0xAF, 0x7B, 0xE3, 0x11, 0x8E, 0x9D, 0x16, 0x61, 0x8C, 0x84, 0x3C, 0x1F, 0x5A,
    0x02, 0x4F, 0x39, 0xFE, 0x04, 0x07, 0x5C, 0x8B, 0xEE, 0x66, 0x33, 0xC4, 0xC8, 0x59, 0xB5, 0x5D,
    0xC2, 0x6C, 0xF6, 0x4D, 0xFB, 0xAE, 0x4A, 0x4B, 0xF3, 0x35, 0x2C, 0xCA, 0x21, 0x78, 0x3B, 0x03,
    0xFD, 0x24, 0xBD, 0x25, 0x37, 0x29, 0xAC, 0x4E, 0xF9, 0x92, 0x3A, 0x32, 0x4C, 0xDA, 0x06, 0x5E,
    0x00, 0x94, 0x60, 0xEC, 0x17, 0x98, 0xD7, 0x3E, 0xCB, 0x6A, 0xA9, 0xD9, 0x9C, 0xBB, 0x08, 0x8F,
    0x40, 0xA0, 0x6F, 0x55, 0x67, 0x87, 0x54, 0x80, 0xB2, 0x36, 0x47, 0x22, 0x44, 0x63, 0x05, 0x6B,
    0xF0, 0x0F, 0xC7, 0x90, 0xC5, 0x65, 0xE2, 0x64, 0xFA, 0xD5, 0xDB, 0x12, 0x7A, 0x0E, 0xD8, 0x7E,
    0x99, 0xD1, 0xE8, 0xD6, 0x86, 0x27, 0xBF, 0xC1, 0x6E, 0xDE, 0x9A, 0x09, 0x0D, 0xAB, 0xE1, 0x91,
    0x56, 0xCD, 0xB3, 0x76, 0x0C, 0xC3, 0xD3, 0x9F, 0x42, 0xB6, 0x9B, 0xE5, 0x23, 0xA7, 0xAD, 0x18,
    0xC6, 0xF4, 0xB8, 0xBE, 0x15, 0x43, 0x70, 0xE0, 0xE7, 0xBC, 0xF1, 0xBA, 0xA5, 0xA6, 0x53, 0x75,
    0xE4, 0xEB, 0xE6, 0x85, 0x14, 0x48, 0xDD, 0x38, 0x2A, 0xCC, 0x7F, 0xB1, 0xC0, 0x71, 0x96, 0xF8,
    0x3F, 0x28, 0xF2, 0x69, 0x74, 0x68, 0xB7, 0xA3, 0x50, 0xD0, 0x79, 0x1D, 0xFC, 0xCE, 0x8A, 0x8D,
    0x2E, 0x62, 0x30, 0xEA, 0xED, 0x2B, 0x26, 0xB9, 0x81, 0x7C, 0x46, 0x89, 0x73, 0xA2, 0xF7, 0x72
};

SocketEngine::SocketEngine() : m_cbRecvRound(0),
m_cbSendRound(0),
m_dwSendXorKey(0),
m_dwRecvXorKey(0),
m_dwSendTickCount(0),
m_dwRecvTickCount(0),
m_dwSendPacketCount(0),
m_dwRecvPacketCount(0) {
    
}
int SocketEngine::getHeadLength() {
    return 8;
}
int SocketEngine::checkFinished(cocos2d::h::HSocketPacket *INpacket) {
    //check data
    const char *buffer = (const char*)INpacket->getBuffer();
    uint16_t wPacketSize = ntohs(*((uint16_t*)(buffer + 2)));
    return wPacketSize - INpacket->getLength();
}
void SocketEngine::encode(HSocketPacket *INpacket) {
    uint8_t buffer[SOCKET_PACKET];
    memcpy(buffer, INpacket->getBuffer(), INpacket->getLength());
    uint16_t wSendSize = EncryptBuffer(buffer, sizeof(CMD_Head) + INpacket->getLength(), sizeof(buffer));
    //    pOverLappedSend->m_WSABuffer.len = wSendSize;
    
    INpacket->setData(buffer, wSendSize);
}
void SocketEngine::decode(HSocketPacket *INpacket) {
    uint8_t buffer[SOCKET_BUFFER];
    memcpy(buffer, INpacket->getBuffer(), INpacket->getLength());
    uint16_t wRecvSize = CrevasseBuffer(buffer, INpacket->getLength());
    
    INpacket->setData(buffer, wRecvSize);
}
uint16_t SocketEngine::EncryptBuffer(uint8_t *pcbDataBuffer, uint16_t wDataSize, uint16_t wBufferSize) {
//    int i = 0;
    //check parameter
    CCAssert(wDataSize >= sizeof(CMD_Head), "");
    CCAssert(wBufferSize >= (wDataSize + 2 * sizeof(uint32_t)), "");
    CCAssert(wDataSize <= (sizeof(CMD_Head) + SOCKET_BUFFER), "");
    
    //adjust length
    uint16_t wEncryptSize = wDataSize - sizeof(CMD_Command), wSnapCount = 0;
    if ((wEncryptSize % sizeof(uint32_t)) != 0)
    {
        wSnapCount = sizeof(uint32_t) - wEncryptSize % sizeof(uint32_t);
        memset(pcbDataBuffer + sizeof(CMD_Info) + wEncryptSize, 0, wSnapCount);
    }
    
    //check code and byte map
    uint8_t cbCheckCode = 0;
    for (uint16_t i = sizeof(CMD_Info); i < wDataSize; i++)
    {
        cbCheckCode += pcbDataBuffer[i];
        pcbDataBuffer[i] = MapSendByte(pcbDataBuffer[i]);
    }
    
    //write info head
    CMD_Head *pHead = (CMD_Head *)pcbDataBuffer;
    pHead->CmdInfo.cbCheckCode = ~cbCheckCode + 1;
    pHead->CmdInfo.wPacketSize = wDataSize;
    pHead->CmdInfo.cbVersion = SOCKET_VER;
    
    //create key
    uint32_t dwXorKey = m_dwSendXorKey;
    if (m_dwSendPacketCount == 0)
    {
        //first generate random seed
        unsigned char Guid[16];
        HCrypto::hex2bin(HNative::generateUuid(), Guid);
        dwXorKey = rand();
        dwXorKey ^= *((uint32_t*)Guid);//Guid.Data1;
        dwXorKey ^= *((uint16_t*)(Guid + 4));//Guid.Data2;
        dwXorKey ^= *((uint16_t*)(Guid + 6));//Guid.Data3;
        dwXorKey ^= *((uint32_t*)(Guid + 8));//*((uint32_t *)Guid.Data4);
//        GUID Guid;
//        CoCreateGuid(&Guid);
//        dwXorKey = GetTickCount() * GetTickCount();
//        dwXorKey ^= Guid.Data1;
//        dwXorKey ^= Guid.Data2;
//        dwXorKey ^= Guid.Data3;
//        dwXorKey ^= *((uint32_t *)Guid.Data4);
        
        //random map seed
        dwXorKey = SeedRandMap((uint16_t)dwXorKey);
        dwXorKey |= ((uint32_t)SeedRandMap((uint16_t)(dwXorKey >> 16))) << 16;
        dwXorKey ^= g_dwPacketKey;
        m_dwSendXorKey = dwXorKey;
        m_dwRecvXorKey = dwXorKey;
    }
    
    //crypto data
    uint16_t *pwSeed = (uint16_t *)(pcbDataBuffer + sizeof(CMD_Info));
    uint32_t *pdwXor = (uint32_t *)(pcbDataBuffer + sizeof(CMD_Info));
    uint16_t wEncrypCount = (wEncryptSize + wSnapCount) / sizeof(uint32_t);
    for (uint16_t i = 0; i < wEncrypCount; i++)
    {
        *pdwXor++ ^= dwXorKey;
        dwXorKey = SeedRandMap(*pwSeed++);
        dwXorKey |= ((uint32_t)SeedRandMap(*pwSeed++)) << 16;
        dwXorKey ^= g_dwPacketKey;
    }
    
    //insert key
    if (m_dwSendPacketCount == 0)
    {
        memmove(pcbDataBuffer + sizeof(CMD_Head) + sizeof(uint32_t), pcbDataBuffer + sizeof(CMD_Head), wDataSize);
        *((uint32_t *)(pcbDataBuffer + sizeof(CMD_Head))) = m_dwSendXorKey;
        pHead->CmdInfo.wPacketSize += sizeof(uint32_t);
        wDataSize += sizeof(uint32_t);
    }
    
    //set attributes
    m_dwSendPacketCount++;
    m_dwSendXorKey = dwXorKey;
	
	//convert net byte sorts
	pHead->CmdInfo.wPacketSize = htons(pHead->CmdInfo.wPacketSize);

    return wDataSize;
}

uint16_t SocketEngine::CrevasseBuffer(uint8_t *pcbDataBuffer, uint16_t wDataSize) {
    uint16_t i = 0;
    //check parameter
    CCAssert(wDataSize >= sizeof(CMD_Head), "");
//    CCAssert(((CMD_Head *)pcbDataBuffer)->CmdInfo.wPacketSize == wDataSize, "");
    
    //adjust length
    uint16_t wSnapCount = 0;
    if ((wDataSize % sizeof(uint32_t)) != 0)
    {
        wSnapCount = sizeof(uint32_t) - wDataSize % sizeof(uint32_t);
        memset(pcbDataBuffer + wDataSize, 0, wSnapCount);
    }
    
//    //提取密钥
////    if (m_dwRecvPacketCount == 0)
//    {
//        CCAssert(wDataSize >= (sizeof(CMD_Head) + sizeof(uint32_t)), "");
////        if (wDataSize < (sizeof(CMD_Head) + sizeof(uint32_t))) throw TEXT("数据包解密长度错误");
//        m_dwRecvXorKey = *(uint32_t *)(pcbDataBuffer + sizeof(CMD_Head));
//        m_dwSendXorKey = m_dwRecvXorKey;
//        memmove(pcbDataBuffer + sizeof(CMD_Head), pcbDataBuffer + sizeof(CMD_Head) + sizeof(uint32_t),
//                   wDataSize - sizeof(CMD_Head) - sizeof(uint32_t));
//        wDataSize -= sizeof(uint32_t);
//        ((CMD_Head *)pcbDataBuffer)->CmdInfo.wPacketSize -= sizeof(uint32_t);
//    }
    
    //decrypto data
    uint32_t dwXorKey = m_dwRecvXorKey;
    uint32_t *pdwXor = (uint32_t *)(pcbDataBuffer + sizeof(CMD_Info));
    uint16_t   *pwSeed = (uint16_t *)(pcbDataBuffer + sizeof(CMD_Info));
    uint16_t wEncrypCount = (wDataSize + wSnapCount - sizeof(CMD_Info)) / 4;
    for (i = 0; i < wEncrypCount; i++)
    {
        if ((i == (wEncrypCount - 1)) && (wSnapCount > 0))
        {
            uint8_t *pcbKey = ((uint8_t *) & m_dwRecvXorKey) + sizeof(uint32_t) - wSnapCount;
            memcpy(pcbDataBuffer + wDataSize, pcbKey, wSnapCount);
        }
        dwXorKey = SeedRandMap(*pwSeed++);
        dwXorKey |= ((uint32_t)SeedRandMap(*pwSeed++)) << 16;
        dwXorKey ^= g_dwPacketKey;
        *pdwXor++ ^= m_dwRecvXorKey;
        m_dwRecvXorKey = dwXorKey;
    }
    
    //check code and byte map
    CMD_Head *pHead = (CMD_Head *)pcbDataBuffer;
    uint8_t cbCheckCode = pHead->CmdInfo.cbCheckCode;;
    for (i = sizeof(CMD_Info); i < wDataSize; i++)
    {
        pcbDataBuffer[i] = MapRecvByte(pcbDataBuffer[i]);
        cbCheckCode += pcbDataBuffer[i];
    }
//    if (cbCheckCode != 0) throw TEXT("数据包效验码错误");
    
    return wDataSize;
}
//random map
uint16_t SocketEngine::SeedRandMap(uint16_t wSeed)
{
    uint32_t dwHold = wSeed;
    return (uint16_t)((dwHold = dwHold * 241103L + 2533101L) >> 16);
}

//map data to send
uint8_t SocketEngine::MapSendByte(uint8_t const cbData)
{
    uint8_t cbMap = g_SendByteMap[(uint8_t)(cbData+m_cbSendRound)];
    m_cbSendRound += 3;
    return cbMap;
}

//map data received
uint8_t SocketEngine::MapRecvByte(uint8_t const cbData)
{
    uint8_t cbMap = g_RecvByteMap[cbData] - m_cbRecvRound;
    m_cbRecvRound += 3;
    return cbMap;
}

NS_CC_H_END
