#include "HHttpResponse.h"

#include "msgpack.hpp"
#include "HHttpRequest.h"
#include "HCrypto.h"

NS_CC_H_BEGIN

void msgpack2js(std::string &ret, const msgpack::object o, bool asKey = false) {
    if (asKey && o.type != msgpack::type::RAW) {
        ret += "\"";
    }
    switch(o.type) {
        case msgpack::type::NIL:
            ret += "null";
            break;
            
        case msgpack::type::BOOLEAN:
            ret += (o.via.boolean ? "true" : "false");
            break;
            
        case msgpack::type::POSITIVE_INTEGER: {
            char a[100] = {0};
            sprintf(a, "%llu", o.via.u64);
            ret += a;
        }
            break;
            
        case msgpack::type::NEGATIVE_INTEGER: {
            char a[100] = {0};
            sprintf(a, "%lld", o.via.i64);
            ret += a;
        }
            break;
            
        case msgpack::type::DOUBLE: {
            char a[100] = {0};
            sprintf(a, "%f", o.via.dec);
            ret += a;
        }
            break;
            
        case msgpack::type::RAW: {
            ret += '"';
            std::string str(o.via.raw.ptr, o.via.raw.size);
            for (auto i = 0; i < str.length(); ++i) {
                if (str[i] == '"') {
                    if (i == 0 || str[i - 1] != '\\') {
                        str.replace(i, 1, "\\\"");
                        ++i;
                    }
                }
            }
            ret.append(str);
            ret += '"';
        }
            break;
            
        case msgpack::type::ARRAY:
            ret += "[";
            if(o.via.array.size != 0) {
                msgpack::object* p(o.via.array.ptr);
                msgpack2js(ret, *p);
                ++p;
                for(msgpack::object* const pend(o.via.array.ptr + o.via.array.size);
                    p < pend; ++p) {
                    ret += ",";
                    msgpack2js(ret, *p);
                }
            }
            ret += "]";
            break;
            
        case msgpack::type::MAP:
            ret += "{";
            if(o.via.map.size != 0) {
                msgpack::object_kv* p(o.via.map.ptr);
                msgpack2js(ret, p->key, true);
                ret += ":";
                msgpack2js(ret, p->val);
                ++p;
                for(msgpack::object_kv* const pend(o.via.map.ptr + o.via.map.size);
                    p < pend; ++p) {
                    ret += ",";
                    msgpack2js(ret, p->key, true);
                    ret += ":";
                    msgpack2js(ret, p->val);
                }
            }
            ret += "}";
            break;
            
        default:
            // FIXME
            ret += "#<UNKNOWN ";
            ret += (uint16_t)o.type;
            ret += ">";
    }
    if (asKey && o.type != msgpack::type::RAW) {
        ret += "\"";
    }
}
HHttpResponse* HHttpResponse::create(network::HttpResponse &response, HHttpRequest &request) {
    HHttpResponse *ret = new HHttpResponse(response, request);
    if (ret) {
        ret->autorelease();
    }
    return ret;
}
HHttpResponse::HHttpResponse(network::HttpResponse &response, HHttpRequest &request)
: _response(response)
, _request(request) {
}
bool HHttpResponse::isSucceed() {
    return _response.isSucceed();
}
std::string HHttpResponse::getResponseData() {
    auto data = _response.getResponseData();
    return std::string(&data->front(), data->size());
}
std::string HHttpResponse::getResponseDataUnpacked() {
    msgpack::unpacker m_unpacker;
    auto size = _response.getResponseData()->size();
    auto str = HCrypto::decodeBase64(&_response.getResponseData()->front(), size);
    size = str.size();
    m_unpacker.reserve_buffer(size);
    memcpy(m_unpacker.buffer(), str.data(), size);
    m_unpacker.buffer_consumed(size);
    
    std::string ret = "{";
    int index = 0;
    char a[100] = {0};
    bool firstItem = true;
    msgpack::unpacked m_unpacked;
    while (m_unpacker.next(&m_unpacked)) {
        if (firstItem) {
            firstItem = false;
        } else {
            ret += ",";
        }
        memset(a, 0, sizeof(a));
        sprintf(a, "\"i%d\":", index);
        ++index;
        ret += a;
        msgpack2js(ret, m_unpacked.get());
    }
    ret += "}";
    return ret;
}
std::string HHttpResponse::getResponseHeader() {
    if (_response.getResponseHeader()->size()) {
        return std::string(&_response.getResponseHeader()->front());
    }
    return std::string("");
}
int HHttpResponse::getResponseCode() {
    return _response.getResponseCode();
}
std::string HHttpResponse::getErrorBuffer() {
    return std::string(_response.getErrorBuffer());
}
HHttpRequest* HHttpResponse::getRequest() {
    return &_request;
}

NS_CC_H_END
