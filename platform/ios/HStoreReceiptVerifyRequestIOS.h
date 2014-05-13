#ifndef __PLATFORM_IOS_HSTORERECEIPTVERIFYREQUESTIOS__
#define __PLATFORM_IOS_HSTORERECEIPTVERIFYREQUESTIOS__

#import <StoreKit/StoreKit.h>
#import "HStoreIOS.h"

#import "cocos2d.h"
#include "network/HttpClient.h"

class HStoreReceiptVerifyRequestIOS : public cocos2d::Ref {
public:
    static HStoreReceiptVerifyRequestIOS* create(HStoreIOS* store,
                                                 SKPaymentTransaction* transaction,
                                                 const char* url,
                                                 bool isRestore);
    ~HStoreReceiptVerifyRequestIOS();
    
    cocos2d::network::HttpRequest* getRequest() {
        return _request;
    }
    
    SKPaymentTransaction* getTransaction() {
        return _transaction;
    }
    
    cocos2d::network::HttpResponse* getResponse() {
        return _response;
    }
    
private:
    void callbackHttpRequest(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
    
private:
    bool init(HStoreIOS* store,
              SKPaymentTransaction* transaction,
              const char* url,
              bool isRestore);
    
    HStoreIOS *_store;
    cocos2d::network::HttpRequest *_request;
    SKPaymentTransaction *_transaction;
    cocos2d::network::HttpResponse *_response;
    bool _isRestore;
};

#endif // __PLATFORM_IOS_HSTORERECEIPTVERIFYREQUESTIOS__
