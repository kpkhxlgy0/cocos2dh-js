#ifndef __HELPER_NETWORK_HHTTPPACKER_H__
#define __HELPER_NETWORK_HHTTPPACKER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Cocos2dxhMacros.h"

namespace msgpack {
    class sbuffer;
    template<typename T> class packer;
}

NS_CC_H_BEGIN

class HHttpPacker : public Ref {
public:
    HHttpPacker();
    ~HHttpPacker();
    void packNil();
    void packBoolean(bool val);
    void packInteger(int val);
    void packDouble(double val);
    void packString(const std::string &val);
    void packArray(int n);
    void packMap(int n);
    std::string getBase64() const;
    std::string getStrEncoded() const;
public:
    static HHttpPacker* create();
private:
    msgpack::sbuffer *_buffer;
    msgpack::packer<msgpack::sbuffer> *_packer;
private:
    friend class HHttpRequest;
};

NS_CC_H_END

#endif //__HELPER_NETWORK_HHTTPPACKER_H__
