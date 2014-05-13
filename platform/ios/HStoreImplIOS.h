#ifndef  __PLATFORM_IOS_HSTOREIMPLIOS__
#define  __PLATFORM_IOS_HSTOREIMPLIOS__

#include "../../helper/store/HStoreImpl.h"

NS_CC_H_BEGIN

class HStoreImplIOS : public HStoreImpl, public HStoreTransactionDelegate {
public:
    ~HStoreImplIOS();
    
    void setDelegate(HStoreTransactionDelegate *delegate) override;

    bool canMakePurchases() const override;
    void restoreCompletedTransactions() override;
    
    void loadProducts(const std::vector<std::string> &productsId, HStoreProductsRequestDelegate *delegate) override;
    void cancelLoadProducts() override;
    bool isProductLoaded(const char *productId) const override;
    bool purchase(const char* productId, int count = 1) override;
    void finishTransaction(HStorePaymentTransaction *transaction) override;
    
    HStorePaymentTransaction::ReceiptVerifyMode getReceiptVerifyMode() const override;
    void setReceiptVerifyMode(HStorePaymentTransaction::ReceiptVerifyMode mode, bool isSandbox = true) override;
    const char* getReceiptVerifyServerUrl() const override;
    void setReceiptVerifyServerUrl(const char* url) override;
    
#pragma mark - delegates
    
    void onTransactionCompleted(HStorePaymentTransaction* transaction) override;
    void onTransactionFailed(HStorePaymentTransaction* transaction, int errorCode, const char *errorString) override;
    void onTransactionRestored(HStorePaymentTransaction* transaction) override;
    void onRestoreCompletedTransactionsFailed(int errorCode, const char *errorString) override;
    void onRestoreCompletedTransactionsFinished() override;
};

NS_CC_H_END

#endif // __PLATFORM_IOS_HSTOREIMPLIOS__
