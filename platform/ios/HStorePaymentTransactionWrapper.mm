//
//#include "HStorePaymentTransactionWrapper.h"
//#import <StoreKit/StoreKit.h>
//
//NS_CC_H_BEGIN
//
//HStorePaymentTransactionWrapper* HStorePaymentTransactionWrapper::createWithTransaction(void* transactionObj) {
//    HStorePaymentTransactionWrapper* transaction = new HStorePaymentTransactionWrapper();
//    transaction->m_transactionObj = transactionObj;
//    [(SKPaymentTransaction *)transactionObj retain];
//    return transaction;
//}
//
//HStorePaymentTransactionWrapper::~HStorePaymentTransactionWrapper(void) {
//    [(SKPaymentTransaction *)m_transactionObj release];
//}
//
//NS_CC_H_END
