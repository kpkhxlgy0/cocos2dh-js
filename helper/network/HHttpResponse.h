#ifndef __HELPER_NETWORK_HHTTPRESPONSE_H__
#define __HELPER_NETWORK_HHTTPRESPONSE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

class HHttpRequest;

class HHttpResponse : public Ref {
public:
    HHttpResponse(network::HttpResponse &response, HHttpRequest& request);
    bool isSucceed();
    std::string getResponseData();
    std::string getResponseDataUnpacked();
    std::string getResponseHeader();
    int getResponseCode();
    std::string getErrorBuffer();
    HHttpRequest* getRequest();
public:
    static HHttpResponse* create(network::HttpResponse &response, HHttpRequest& request);
private:
    network::HttpResponse &_response;
    HHttpRequest &_request;
};

NS_CC_H_END

#endif //__HELPER_NETWORK_HHTTPRESPONSE_H__
