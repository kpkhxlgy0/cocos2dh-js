
#ifndef __HELPER_STORE_HSTOREPAYMENTTRANSACTION_H__
#define __HELPER_STORE_HSTOREPAYMENTTRANSACTION_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

class HStorePaymentTransaction : public Ref {
public:
    enum class ReceiptVerifyMode {
        None,
        Device,
        Server
    };
    enum class ReceiptVerifyStatus {
        UnknownError = -5,
        InvalidReceipt,
        RequestFailed,
        InvalidResult,
        None,
        OK
    };
    enum class State {
        Null,
        Purchasing,
        Purchased,
        Failed,
        Restored,
        Cancelled
    };
public:
    ~HStorePaymentTransaction();
    
    const void* getTransactionData() {
        return _transactionData;
    }
    HStorePaymentTransaction::State getTransactionState() {
        return _state;
    }
    const std::string& getTransactionIdentifier() {
        return _identifier;
    }
    const std::string& getProductIdentifier() {
        return _identifierProduct;
    }
    int getQuantity() {
        return _quantity;
    }
    double getDateTime() {
        return _dateTime;
    }
    int getReceiptDataLength() {
        return _receiptDataLength;
    }
    const void* const getReceiptData() {
        return _receiptData;
    }
    int getErrorCode() {
        return _errorCode;
    }
    const std::string& getErrorDescription() {
        return _errorDescription;
    }
    HStorePaymentTransaction* getOriginalTransaction() {
        return _originalTransaction;
    }
    HStorePaymentTransaction::ReceiptVerifyMode getReceiptVerifyMode() {
        return _receiptVerifyMode;
    }
    HStorePaymentTransaction::ReceiptVerifyStatus getReceiptVerifyStatus() {
        return _receiptVerifyStatus;
    }
public:
    static HStorePaymentTransaction* create(void *transactionData,
                                            HStorePaymentTransaction::State state,
                                            const std::string &transactionId,
                                            const std::string &productId,
                                            int quantity,
                                            double dateTime,
                                            int receiptDataLength,
                                            const void *receiptData,
                                            int errorCode,
                                            const std::string &errorDescription,
                                            HStorePaymentTransaction *originalTransaction,
                                            HStorePaymentTransaction::ReceiptVerifyMode receiptVerifyMode,
                                            HStorePaymentTransaction::ReceiptVerifyStatus receiptVerifyStatus);
private:
    HStorePaymentTransaction(void) {}
    
    bool init(void *transactionData,
                       HStorePaymentTransaction::State state,
                       const std::string &transactionId,
                       const std::string &productId,
                       int quantity,
                       double dateTime,
                       int receiptDataLength,
                       const void *receiptData,
                       int errorCode,
                       const std::string &errorDescription,
                       HStorePaymentTransaction *originalTransaction,
                       HStorePaymentTransaction::ReceiptVerifyMode receiptVerifyMode,
                       HStorePaymentTransaction::ReceiptVerifyStatus receiptVerifyStatus);
    
    void *_transactionData;
    HStorePaymentTransaction::State _state;
    std::string _identifier;
    std::string _identifierProduct;
    int _quantity;
    double _dateTime;
    int _receiptDataLength;
    void *_receiptData;
    int _errorCode;
    std::string _errorDescription;
    HStorePaymentTransaction *_originalTransaction;
    HStorePaymentTransaction::ReceiptVerifyMode _receiptVerifyMode;
    HStorePaymentTransaction::ReceiptVerifyStatus _receiptVerifyStatus;
};

NS_CC_H_END

#endif // __HELPER_STORE_HSTOREPAYMENTTRANSACTION_H__
