#ifndef  __PLATFORM_ANDROID_HSTOREIMPLANDROID__
#define  __PLATFORM_ANDROID_HSTOREIMPLANDROID__

#include "../../quick/store/HStoreImpl.h"

NS_CC_H_BEGIN

class HStoreImplAndroid : public HStoreImpl, public CCStoreTransactionObserver {
public:
    ~HStoreImplAndroid();
    
    void postInitWithTransactionObserver(CCStoreTransactionObserver* observer);

    void registerStoreScriptHandler(int INhandler);
    void unregisterStoreScriptHandler();
    void handleScriptStoreCompleted(CCStorePaymentTransaction* transaction);
    void handleScriptStoreFailed(CCStorePaymentTransaction* transaction);
    void handleScriptStoreRestored(CCStorePaymentTransaction* transaction);

    
    bool canMakePurchases(void);
    
    void loadProducts(CCArray* productsId, CCStoreProductsRequestDelegate* delegate);
    void loadProducts(CCArray* productsId, int INhandler);

    void cancelLoadProducts(void);
    bool isProductLoaded(const char* productId);
    bool purchase(const char* productId);
    void finishTransaction(CCStorePaymentTransaction *transaction);
    
    CCStoreReceiptVerifyMode getReceiptVerifyMode(void);
    void setReceiptVerifyMode(CCStoreReceiptVerifyMode mode, CCStoreIsSandbox isSandbox = true);
    const char* getReceiptVerifyServerUrl(void);
    void setReceiptVerifyServerUrl(const char* url);
    const char* getUserAccount();
    void setUserAccount(const char *INaccount);
    const char* getPostHeaderName();
    void setPostHeaderName(const char *INheaderName);
    const char* getStatusHeaderKey();
    void setStatusHeaderKey(const char *INkey);
    const char* getSuccessHeaderValue();
    void setSuccessHeaderValue(const char *INvalue);
    
#pragma mark - delegates
    virtual void transactionCompleted(CCStorePaymentTransaction* transaction);
    virtual void transactionFailed(CCStorePaymentTransaction* transaction);
    virtual void transactionRestored(CCStorePaymentTransaction* transaction);
};

NS_CC_H_END

#endif // __PLATFORM_ANDROID_HSTOREIMPLANDROID__
