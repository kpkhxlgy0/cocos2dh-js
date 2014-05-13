#ifndef  __PLATFORM_IOS_HSTOREIMPL__
#define  __PLATFORM_IOS_HSTOREIMPL__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"
#include "HStoreProduct.h"
#include "HStorePaymentTransaction.h"

#include "HStore.h"

NS_CC_H_BEGIN

class HStoreImpl {
public:
    virtual ~HStoreImpl() {
        for (auto it = _transactions.begin(); it != _transactions.end(); ++it) {
            it->second->release();
        }
    }
    
    virtual void setDelegate(HStoreTransactionDelegate *delegate) = 0;
    
    virtual bool canMakePurchases() const = 0;
    virtual void restoreCompletedTransactions() = 0;
    
    virtual void loadProducts(const std::vector<std::string> &productsId, HStoreProductsRequestDelegate *delegate) = 0;
    virtual void cancelLoadProducts(void) = 0;
    virtual bool isProductLoaded(const char *productId) const = 0;
    virtual bool purchase(const char *productId, int count = 1) = 0;
    virtual void finishTransaction(HStorePaymentTransaction *transaction) = 0;

    virtual HStorePaymentTransaction::ReceiptVerifyMode getReceiptVerifyMode() const = 0;
    virtual void setReceiptVerifyMode(HStorePaymentTransaction::ReceiptVerifyMode mode, bool isSandbox = true) = 0;
    virtual const char* getReceiptVerifyServerUrl() const = 0;
    virtual void setReceiptVerifyServerUrl(const char* url) = 0;
    
    const std::string& getUserAccount() const {
        return _userAccount;
    }
    void setUserAccount(const std::string &account) {
        _userAccount = account;
    }
protected:
    HStoreImpl()
    : _delegate(nullptr)
    , _isLoadProductsLuaNotCompleted(false)
    , _storeScriptHandler(0) {
    }
    virtual bool init() {
        return true;
    }

protected:
    HStoreTransactionDelegate* _delegate;
    int _storeScriptHandler;
    bool _isLoadProductsLuaNotCompleted;
    HStore::PaymentTransactions _transactions;
    
    std::string _userAccount;
};

// This method must be implemented at each subclass of HStoreImpl.
extern HStoreImpl* __createHStoreImpl();

NS_CC_H_END

#endif // __PLATFORM_IOS_HSTOREIMPL__
