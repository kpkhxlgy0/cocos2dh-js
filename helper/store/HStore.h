
#ifndef  __HELPER_STORE_HSTORE_H__
#define  __HELPER_STORE_HSTORE_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"
#include "HStoreProduct.h"
#include "HStorePaymentTransaction.h"

NS_CC_H_BEGIN

class HStoreTransactionDelegate;
class HStoreProductsRequestDelegate;
class HStoreImpl;

class HStore : public Ref {
public:
    enum class ProductRequestError {
        PreviousRequestNotCompleted = -2,
        Cancelled
    };
    using PaymentTransactions = std::map<const std::string, HStorePaymentTransaction*>;
    using PaymentTransactionsIterator = PaymentTransactions::iterator;
public:
    HStore();
    ~HStore();
    
    void setDelegate(HStoreTransactionDelegate *delegate);
    
    bool canMakePurchases() const;
    void restoreCompletedTransactions();
    
    void loadProducts(const std::vector<std::string> &productsId, HStoreProductsRequestDelegate *delegate);
    void cancelLoadProducts();
    bool isProductLoaded(const char *productId) const;
    bool purchase(const char *productId, int count = 1);
    void finishTransaction(HStorePaymentTransaction *transaction);

    HStorePaymentTransaction::ReceiptVerifyMode getReceiptVerifyMode() const;
    void setReceiptVerifyMode(HStorePaymentTransaction::ReceiptVerifyMode mode, bool isSandbox = true);
    const char* getReceiptVerifyServerUrl() const;
    void setReceiptVerifyServerUrl(const char* url);
    
    const std::string& getUserAccount() const;
    void setUserAccount(const std::string &account);
public:
    static HStore* getInstance();
    static void destroyInstance();
private:
    bool init();
    HStoreImpl* _storeImpl;
    HStoreTransactionDelegate *_delegateTransaction;
    HStoreProductsRequestDelegate *_delegateProduct;
};

class HStoreTransactionDelegate {
public:
    virtual void onTransactionCompleted(HStorePaymentTransaction *transaction) = 0;
    virtual void onTransactionFailed(HStorePaymentTransaction *transaction, int errorCode, const char *errorString) = 0;
    virtual void onTransactionRestored(HStorePaymentTransaction *transaction) = 0;
    virtual void onRestoreCompletedTransactionsFailed(int errorCode, const char *errorString) = 0;
    virtual void onRestoreCompletedTransactionsFinished() = 0;
};

class HStoreProductsRequestDelegate {
public:
    virtual void onRequestProductsCompleted(const std::vector<HStoreProduct*> &products,
                                            const std::vector<std::string> &invalidProductsId) = 0;
    virtual void onRequestProductsFailed(HStore::ProductRequestError errorCode, const char *errorString) = 0;
};

NS_CC_H_END

#endif // __HELPER_STORE_HSTORE_H__
