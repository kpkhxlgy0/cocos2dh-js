/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   socket包体操作类
 @History       (操作 -- 创建)(时间 -- 13-2-26)
 */

#include "HSocketPacket.h"
#include "../HSocket.h"
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include <netinet/in.h>
#endif

NS_CC_H_BEGIN

HSocketPacket::HSocketPacket(bool INuseCode) : m_buffer(NULL),
m_size(0),
m_length(0),
m_index(0),
m_useCode(INuseCode) {
}
HSocketPacket::~HSocketPacket() {
    free(m_buffer);
}
void HSocketPacket::setData(const void *INdata, size_t INsize) {
    m_size = INsize;
    m_length = INsize;
    m_index = 0;
    free(m_buffer);
    m_buffer = (char*)malloc(INsize);
    memcpy(m_buffer, INdata, INsize);
}
bool HSocketPacket::isUseCode() {
    return m_useCode;
}
void HSocketPacket::writeInt8(int8_t INvalue) {
    checkSize(1);
    *((int8_t*)(m_buffer + m_length)) = INvalue;
    m_length += 1;
}
void HSocketPacket::writeUInt8(uint8_t INvalue) {
    checkSize(1);
    *((uint8_t*)(m_buffer + m_length)) = INvalue;
    m_length += 1;
}
void HSocketPacket::writeInt16(int16_t INvalue) {
    checkSize(2);
    *((int16_t*)(m_buffer + m_length)) = htons(INvalue);
    m_length += 2;
}
void HSocketPacket::writeUInt16(uint16_t INvalue) {
    checkSize(2);
    *((uint16_t*)(m_buffer + m_length)) = htons(INvalue);
    m_length += 2;
}
void HSocketPacket::writeInt32(int32_t INvalue) {
    checkSize(4);
    *((int32_t*)(m_buffer + m_length)) = htonl(INvalue);
    m_length += 4;
}
void HSocketPacket::writeUInt32(uint32_t INvalue) {
    checkSize(4);
    *((uint32_t*)(m_buffer + m_length)) = htonl(INvalue);
    m_length += 4;
}
void HSocketPacket::writeInt64(int64_t INvalue) {
    checkSize(8);
    *((int64_t*)(m_buffer + m_length)) = htonll(INvalue);
    m_length += 8;
}
void HSocketPacket::writeUInt64(uint64_t INvalue) {
    checkSize(8);
    *((uint64_t*)(m_buffer + m_length)) = htonll(INvalue);
    m_length += 8;
}
void HSocketPacket::writeFloat(float INvalue) {
    int32_t temp = htonl(*((int32_t*)(&INvalue)));
    writeData(&temp, 4);
}
void HSocketPacket::writeDouble(double INvalue) {
    int64_t temp = htonll(*((int64_t*)(&INvalue)));
    writeData(&temp, 8);
}
void HSocketPacket::writeData(const void *INdata, size_t INsize) {
    checkSize(INsize);
    memcpy(m_buffer + m_length, INdata, INsize);
    m_length += INsize;
}
void HSocketPacket::readInt8(int8_t *OUTvalue) {
    *OUTvalue = *((int8_t*)(m_buffer + m_index));
    m_index += 1;
}
void HSocketPacket::readUInt8(uint8_t *OUTvalue) {
    *OUTvalue = *((uint8_t*)(m_buffer + m_index));
    m_index += 1;
}
void HSocketPacket::readInt16(int16_t *OUTvalue) {
    *OUTvalue = ntohs(*((int16_t*)(m_buffer + m_index)));
    m_index += 2;
}
void HSocketPacket::readUInt16(uint16_t *OUTvalue) {
    *OUTvalue = ntohs(*((uint16_t*)(m_buffer + m_index)));
    m_index += 2;
}
void HSocketPacket::readInt32(int32_t *OUTvalue) {
    *OUTvalue = ntohl(*((int32_t*)(m_buffer + m_index)));
    m_index += 4;
}
void HSocketPacket::readUInt32(uint32_t *OUTvalue) {
    *OUTvalue = ntohl(*((uint32_t*)(m_buffer + m_index)));
    m_index += 4;
}
void HSocketPacket::readInt64(int64_t *OUTvalue) {
    *OUTvalue = ntohll(*((int64_t*)(m_buffer + m_index)));
    m_index += 8;
}
void HSocketPacket::readUInt64(uint64_t *OUTvalue) {
    *OUTvalue = ntohll(*((uint64_t*)(m_buffer + m_index)));
    m_index += 8;
}
void HSocketPacket::readFloat(float *OUTvalue) {
    int32_t tempValue;
    readData(&tempValue, 4);
    int32_t temp = ntohl(tempValue);
    memcpy(OUTvalue, &temp, 4);
}
void HSocketPacket::readDouble(double *OUTvalue) {
    int64_t tempValue;
    readData(&tempValue, 8);
    int64_t temp = ntohll(tempValue);
    memcpy(OUTvalue, &temp, 8);
}
void HSocketPacket::readData(void *OUTdata, size_t INsize) {
    memcpy(OUTdata, m_buffer + m_index, INsize);
    m_index += INsize;
}
const char* HSocketPacket::getBuffer() {
    return m_buffer;
}
size_t HSocketPacket::getLength() {
    return m_length;
}
void HSocketPacket::checkSize(size_t INsize) {
    if (m_length + INsize > m_size) {
        if (m_size == 0) {
            m_size = 1;
        }
        while (m_length + INsize > m_size) {
            m_size *= 2;
        }
        char *temp = (char*)malloc(m_size);
        memcpy(temp, m_buffer, m_length);
        free(m_buffer);
        m_buffer = temp;
    }
}
void HSocketPacket::print() {
    CCLOG("CHSocketPacket::print begin");
    for (size_t i = 0; i < m_length; ++i) {
        CCLOG("%u", m_buffer[i]);
    }
    CCLOG("CHSocketPacket::print end");
}

NS_CC_H_END