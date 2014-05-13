#ifndef __HELPER_NETWORK_HHTTPREQUEST_H__
#define __HELPER_NETWORK_HHTTPREQUEST_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

class HHttpPacker;
class HHttpResponse;

class HHttpRequestDelegate {
public:
    virtual ~HHttpRequestDelegate() {}
    virtual void onReceiveHttpPacket(HHttpResponse *response) = 0;
};

class HHttpRequest : public Ref {
public:
    HHttpRequest();
    void setRequestType(network::HttpRequest::Type type);
    void setUrl(const char* url);
    void setDelegate(HHttpRequestDelegate *delegate);
    void setHeaders(const std::vector<std::string> &headers);
    void addPacker(const char *name, HHttpPacker *packer);
    void addData(const char *name, const std::string &data);
    void addPackerParam(const char *name, HHttpPacker *packer);
    void addDataParam(const char *name, const std::string &data);
    void send();
    /** Override autorelease method to avoid developers to call it */
    Ref* autorelease() {
        CCASSERT(false, "HttpResponse is used between network thread and ui thread \
                 therefore, autorelease is forbidden here");
        return nullptr;
    }
    void setTimeoutForConnect(int value);
    int getTimeoutForConnect() const;
    void setTimeoutForRead(int value);
    int getTimeoutForRead() const;
public:
    static std::string encodeUrl(const char* src);
    static std::string decodeUrl(const char* src);
private:
    void callback(network::HttpClient* client, network::HttpResponse* response);
private:
    network::HttpRequest *_request;
    std::string _data;
    HHttpRequestDelegate *_delegate;
    std::string _param;
    int _timeoutForConnectPre;
    int _timeoutForReadPre;
};

NS_CC_H_END

#endif //__HELPER_NETWORK_HHTTPREQUEST_H__
