#include "HMSPacket.h"

#include "msgpack.hpp"

#define MSGPACK_UNPACK(TYPE) m_unpacker->next(m_unpacked); \
TYPE value; \
m_unpacked->get().convert(&value); \
return value;

#define MSGPACK_PACK(INvalue) m_packer->pack(INvalue);

NS_CC_H_BEGIN


HMSPacket* HMSPacket::create() {
    auto ret = new HMSPacket();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HMSPacket::HMSPacket()
    : m_buffer(nullptr)
    , m_packer(nullptr)
    , m_unpacker(nullptr)
    , m_unpacked(nullptr)
    , _bufToSend(nullptr) {
    
}

HMSPacket::~HMSPacket() {
    delete m_buffer;
    delete m_packer;
    delete m_unpacker;
    delete m_unpacked;
    delete [] _bufToSend;
}

bool HMSPacket::init() {
    m_unpacked = new msgpack::unpacked();
    return true;
}

void HMSPacket::beginRead(const char *INbuffer, size_t INsize) {
    delete m_unpacker;
    m_unpacker = new msgpack::unpacker();
    m_unpacker->reserve_buffer(INsize);
    memcpy(m_unpacker->buffer(), INbuffer, INsize);
    m_unpacker->buffer_consumed(INsize);
}

bool HMSPacket::readBool() {
    MSGPACK_UNPACK(bool);
}

int8_t HMSPacket::readInt8() {
    MSGPACK_UNPACK(int8_t);
}

uint8_t HMSPacket::readUInt8() {
    MSGPACK_UNPACK(int8_t);
}

int16_t HMSPacket::readInt16() {
    MSGPACK_UNPACK(int16_t);
}

uint16_t HMSPacket::readUInt16() {
    MSGPACK_UNPACK(uint16_t);
}

int32_t HMSPacket::readInt32() {
    MSGPACK_UNPACK(int32_t);
}

uint32_t HMSPacket::readUInt32() {
    MSGPACK_UNPACK(uint32_t);
}

int64_t HMSPacket::readInt64() {
    MSGPACK_UNPACK(int64_t);
}

uint64_t HMSPacket::readUInt64() {
    MSGPACK_UNPACK(uint64_t);
}

float HMSPacket::readFloat() {
    MSGPACK_UNPACK(float);
}

double HMSPacket::readDouble() {
    MSGPACK_UNPACK(double);
}

std::string HMSPacket::readString() {
    MSGPACK_UNPACK(std::string);
}

std::string HMSPacket::readBuffer() {
//    uint8_t len;
//    m_unpacker->next(m_unpacked);
//    m_unpacked->get().convert(&len);
//    uint8_t *a = new uint8_t[len];
//    memset(a, 0, len);
//    for (size_t i = 0; i < len; ++i) {
//        m_unpacker->next(m_unpacked);
//        m_unpacked->get().convert(a + i);
//    }
//    std::string ret((const char*)a, len);
//    delete[] a;
//    return ret;
    msgpack::type::raw_ref raw;
    m_unpacker->next(m_unpacked);
    m_unpacked->get().convert(&raw);
    std::string ret((const char*)raw.ptr, raw.size);
    return ret;
}

void HMSPacket::beginWrite() {
    delete m_buffer;
    m_buffer = new msgpack::sbuffer();
    delete m_packer;
    m_packer = new msgpack::packer<msgpack::sbuffer>(m_buffer);
}

void HMSPacket::writeBool(bool INvalue) {
    MSGPACK_PACK(INvalue);
}

void HMSPacket::writeInt8(char INvalue) {
    MSGPACK_PACK((signed char)INvalue);
}

void HMSPacket::writeUInt8(uint8_t INvalue) {
    MSGPACK_PACK(INvalue);
}

void HMSPacket::writeInt16(int16_t INvalue) {
    MSGPACK_PACK(INvalue);
}

void HMSPacket::writeUInt16(uint16_t INvalue) {
    MSGPACK_PACK(INvalue);
}

void HMSPacket::writeInt32(int32_t INvalue) {
    MSGPACK_PACK(INvalue);
}

void HMSPacket::writeUInt32(uint32_t INvalue) {
    MSGPACK_PACK(INvalue);
}

void HMSPacket::writeInt64(int64_t INvalue) {
    MSGPACK_PACK(INvalue);
}

void HMSPacket::writeUInt64(uint64_t INvalue) {
    MSGPACK_PACK(INvalue);
}

void HMSPacket::writeFloat(float INvalue) {
    MSGPACK_PACK(INvalue);
}

void HMSPacket::writeDouble(double INvalue) {
    MSGPACK_PACK(INvalue);
}

void HMSPacket::writeString(const std::string &INvalue) {
    MSGPACK_PACK(INvalue);
}

void HMSPacket::writeBuffer(const char *INvalue, size_t INlen) {
    m_packer->pack_raw(INlen);
    m_packer->pack_raw_body(INvalue, INlen);
}

void HMSPacket::setRoute(uint32_t route) {
    _route = route;
}

uint32_t HMSPacket::getRoute() const {
    return _route;
}

void HMSPacket::setCmdKey(uint16_t cmdKey) {
    _cmdKey = cmdKey;
}

uint16_t HMSPacket::getCmdKey() const {
    return _cmdKey;
}

const char* HMSPacket::getBuffer() {
    uint16_t bufferLen = m_buffer->size() + 12;
    delete [] _bufToSend;
    _bufToSend = new char[bufferLen];
    *((uint16_t*)_bufToSend) = htons(bufferLen);
    uint64_t route = _route;
    *((uint64_t*)(_bufToSend + 2)) = htonll(route);
    *((uint16_t*)(_bufToSend + 10)) = htons(_cmdKey);
    memcpy(_bufToSend + 12, m_buffer->data(), m_buffer->size());
    return _bufToSend;
}

size_t HMSPacket::getLength() {
    return m_buffer->size() + 12;
}

NS_CC_H_END
