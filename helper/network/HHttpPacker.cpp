#include "HHttpPacker.h"
#include "../crypto/HCrypto.h"
#include "msgpack.hpp"

NS_CC_H_BEGIN

HHttpPacker* HHttpPacker::create() {
    auto ret = new HHttpPacker();
    ret->autorelease();
    return ret;
}

HHttpPacker::HHttpPacker() {
    _buffer = new msgpack::sbuffer();
    _packer = new msgpack::packer<msgpack::sbuffer>(_buffer);
}

HHttpPacker::~HHttpPacker() {
    delete _buffer;
    delete _packer;
}

void HHttpPacker::packNil() {
    _packer->pack_nil();
}
void HHttpPacker::packBoolean(bool val) {
    _packer->pack(val);
}
void HHttpPacker::packInteger(int val) {
    _packer->pack(val);
}
void HHttpPacker::packDouble(double val) {
    _packer->pack(val);
}
void HHttpPacker::packString(const std::string &val) {
    _packer->pack(val);
}
void HHttpPacker::packArray(int n) {
    _packer->pack_array(n);
}
void HHttpPacker::packMap(int n) {
    _packer->pack_map(n);
}
std::string HHttpPacker::getBase64() const {
    return HCrypto::encodeBase64(_buffer->data(), _buffer->size());
}
std::string HHttpPacker::getStrEncoded() const {
    return HCrypto::encodeUrl(getBase64().c_str());
}

NS_CC_H_END
