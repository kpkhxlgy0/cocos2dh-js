#include "HBFPacket.h"

NS_CC_H_BEGIN


HBFPacket* HBFPacket::create() {
    auto ret = new HBFPacket();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HBFPacket::HBFPacket()
    : _bufToSend(nullptr) {
    
}

HBFPacket::~HBFPacket() {
    delete [] _bufToSend;
}

bool HBFPacket::init() {
    return true;
}

void HBFPacket::beginRead(const char *buffer, size_t size) {
    _buffer.reserve(size);
    _buffer.insert(_buffer.end(), buffer, buffer + size);
}

std::string HBFPacket::readString() {
    return std::string(&_buffer.front(), _buffer.size());
}

void HBFPacket::beginWrite() {
    _buffer.clear();
}
void HBFPacket::writeString(const std::string &value) {
    for (auto v : value) {
        _buffer.push_back(v);
    }
}

const char* HBFPacket::getBuffer() {
    uint16_t bufferLen = _buffer.size() + 2;
    delete [] _bufToSend;
    _bufToSend = new char[bufferLen];
    *((uint16_t*)_bufToSend) = htons(bufferLen);
    memcpy(_bufToSend + 2, &_buffer.front(), _buffer.size());
    return _bufToSend;
}

size_t HBFPacket::getLength() {
    return _buffer.size() + 2;
}

NS_CC_H_END
