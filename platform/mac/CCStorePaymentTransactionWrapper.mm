
#include "CCStorePaymentTransactionWrapper.h"
#import <StoreKit/StoreKit.h>

NS_CC_H_BEGIN

CCStorePaymentTransactionWrapper* CCStorePaymentTransactionWrapper::createWithTransaction(void* transactionObj)
{
    CCStorePaymentTransactionWrapper* transaction = new CCStorePaymentTransactionWrapper();
    transaction->m_transactionObj = transactionObj;
    [(SKPaymentTransaction *)transactionObj retain];
    return transaction;
}

CCStorePaymentTransactionWrapper::~CCStorePaymentTransactionWrapper(void)
{
    [(SKPaymentTransaction *)m_transactionObj release];
}

NS_CC_H_END
