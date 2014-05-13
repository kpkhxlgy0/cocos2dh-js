#include "HStoreReceiptVerifyRequestIOS.h"

using namespace cocos2d::network;

HStoreReceiptVerifyRequestIOS* HStoreReceiptVerifyRequestIOS::create(HStoreIOS* store,
                                                                     SKPaymentTransaction* transaction,
                                                                     const char* url,
                                                                     bool isRestore)
{
    HStoreReceiptVerifyRequestIOS* handler = new HStoreReceiptVerifyRequestIOS();
    handler->init(store, transaction, url, isRestore);
    return handler;
}

bool HStoreReceiptVerifyRequestIOS::init(HStoreIOS* store,
                                         SKPaymentTransaction* transaction,
                                         const char* url,
                                         bool isRestore)
{
    _store = store;
    [_store retain];
    _transaction = transaction;
    [_transaction retain];
    _request = new HttpRequest();
    _request->setResponseCallback(this, httpresponse_selector(HStoreReceiptVerifyRequestIOS::callbackHttpRequest));
    _request->setUrl(url);
    _request->setRequestType(HttpRequest::Type::POST);
    _isRestore = isRestore;
    return true;
}

HStoreReceiptVerifyRequestIOS::~HStoreReceiptVerifyRequestIOS(void)
{
    [_transaction release];
    CC_SAFE_RELEASE(_request);
    CCLOG("~~ delete CCStoreReceiptVerifyRequestIOS");
}

void HStoreReceiptVerifyRequestIOS::callbackHttpRequest(HttpClient* client, HttpResponse* response) {
    _response = response;
    if (response->isSucceed()) {
        [_store verifyReceiptRequestFinished: this withType:_isRestore];
    } else {
        [_store verifyReceiptRequestFailed: this withType:_isRestore];
    }
    [_store release];
    release();
}
