#include "HHttpRequest.h"

#include "msgpack.hpp"
#include "HHttpPacker.h"
#include "HHttpResponse.h"
#include "../crypto/HCrypto.h"

using namespace cocos2d::network;

NS_CC_H_BEGIN

HHttpRequest::HHttpRequest() : _delegate(nullptr) {
    _request = new network::HttpRequest();
}

void HHttpRequest::setRequestType(network::HttpRequest::Type type) {
    _request->setRequestType(type);
}
void HHttpRequest::setUrl(const char* url) {
    _request->setUrl(url);
}
void HHttpRequest::setDelegate(HHttpRequestDelegate *delegate) {
    Ref *obj = dynamic_cast<Ref*>(_delegate);
    CC_SAFE_RELEASE(obj);
    obj = dynamic_cast<Ref*>(delegate);
    CC_SAFE_RETAIN(obj);
    _delegate = delegate;
}
void HHttpRequest::setHeaders(const std::vector<std::string> &headers) {
    _request->setHeaders(headers);
}
void HHttpRequest::addPacker(const char *name, HHttpPacker *packer) {
    addData(name, packer->getStrEncoded());
}
void HHttpRequest::addData(const char *name, const std::string &data) {
    if (!_data.empty()) {
        _data += "&";
    }
    _data += name;
    _data += "=";
    _data += data;
}
void HHttpRequest::addPackerParam(const char *name, HHttpPacker *packer) {
    addDataParam(name, packer->getStrEncoded());
}
void HHttpRequest::addDataParam(const char *name, const std::string &data) {
    if (!_param.empty()) {
        _param += "&";
    } else {
        _param += "?";
    }
    _param += name;
    _param += "=";
    _param += data;
}
void HHttpRequest::send() {
    _request->setResponseCallback(this, httpresponse_selector(HHttpRequest::callback));
    if (_request->getRequestType() == HttpRequest::Type::GET) {
        std::string url = _request->getUrl();
        url += _param;
        _request->setUrl(url.c_str());
    } else {
        _request->setRequestData(_data.c_str(), _data.length());
    }
    HttpClient::getInstance()->send(_request);
}
void HHttpRequest::setTimeoutForConnect(int value) {
    auto client = HttpClient::getInstance();
    _timeoutForConnectPre = client->getTimeoutForConnect();
    client->setTimeoutForConnect(value);
}
int HHttpRequest::getTimeoutForConnect() const {
    return HttpClient::getInstance()->getTimeoutForConnect();
}
void HHttpRequest::setTimeoutForRead(int value) {
    auto client = HttpClient::getInstance();
    _timeoutForReadPre = client->getTimeoutForRead();
    client->setTimeoutForRead(value);
}
int HHttpRequest::getTimeoutForRead() const {
    return HttpClient::getInstance()->getTimeoutForRead();
}
std::string HHttpRequest::encodeUrl(const char *src) {
    return HCrypto::encodeUrl(src);
}
std::string HHttpRequest::decodeUrl(const char* src) {
    return HCrypto::decodeUrl(src);
}
void HHttpRequest::callback(network::HttpClient *client, network::HttpResponse *response) {
    client->setTimeoutForConnect(_timeoutForConnectPre);
    client->setTimeoutForRead(_timeoutForReadPre);
    if (_delegate) {
        HHttpResponse *res = HHttpResponse::create(*response, *this);
        _delegate->onReceiveHttpPacket(res);
    }
    if (PoolManager::getInstance()->isObjectInPools(this)) {
        while (getReferenceCount() > 1) {
            release();
        }
    } else {
        release();
    }
}

NS_CC_H_END
