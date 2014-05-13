
#include "HStorePaymentTransaction.h"

NS_CC_H_BEGIN

HStorePaymentTransaction* HStorePaymentTransaction::create(void *transactionData,
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
                                                           HStorePaymentTransaction::ReceiptVerifyStatus receiptVerifyStatus) {
    auto ret = new HStorePaymentTransaction();
    if (ret && ret->init(transactionData,
                         state,
                         transactionId,
                         productId,
                         quantity,
                         dateTime,
                         receiptDataLength,
                         receiptData,
                         errorCode,
                         errorDescription,
                         originalTransaction,
                         receiptVerifyMode,
                         receiptVerifyStatus)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HStorePaymentTransaction::~HStorePaymentTransaction(void)
{
    CC_SAFE_RELEASE(_originalTransaction);
    if (_receiptData) {
        free(_receiptData);
    }
//    if (_transactionData) {
//        delete _transactionData;
//    }
    
    CCLOG("~~ CCStorePaymentTransaction::~CCStorePaymentTransaction()");
}

bool HStorePaymentTransaction::init(void *transactionData,
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
                                    HStorePaymentTransaction::ReceiptVerifyStatus receiptVerifyStatus)
{
    _transactionData = transactionData;
    _state = state;
    _identifier = transactionId;
    _identifierProduct = productId;
    _quantity = quantity;
    _dateTime = dateTime;
    _receiptDataLength = receiptDataLength;
    if (receiptDataLength > 0) {
        _receiptData = malloc(receiptDataLength + 1);
        memset(_receiptData, 0, receiptDataLength + 1);
        memcpy(_receiptData, receiptData, receiptDataLength);
    } else {
        _receiptData = nullptr;
    }
    _errorCode = errorCode;
    _errorDescription = errorDescription;
    _originalTransaction = originalTransaction;
    CC_SAFE_RETAIN(_originalTransaction);
    
    _receiptVerifyMode = receiptVerifyMode;
    _receiptVerifyStatus = receiptVerifyStatus;
    return true;
}

NS_CC_H_END
