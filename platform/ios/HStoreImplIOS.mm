
#include "HStoreImplIOS.h"

#import "HStoreIOS.h"

using namespace std;

NS_CC_H_BEGIN

HStoreImpl* __createHStoreImpl() {
    return new HStoreImplIOS();
}

HStoreImplIOS::~HStoreImplIOS() {
    [HStoreIOS destroyInstance];
}

void HStoreImplIOS::setDelegate(HStoreTransactionDelegate *delegate) {
    _delegate = delegate;
    [[HStoreIOS getInstance] setDelegate:this];
}

bool HStoreImplIOS::canMakePurchases() const {
    return [[HStoreIOS getInstance] canMakePurchases];
}

void HStoreImplIOS::restoreCompletedTransactions() {
    return [[HStoreIOS getInstance] restoreCompletedTransactions];
}

void HStoreImplIOS::loadProducts(const vector<string> &productsId, HStoreProductsRequestDelegate *delegate) {
    NSMutableSet* set = [NSMutableSet set];
    for_each(productsId.begin(), productsId.end(), [&set](const string &item) {
        [set addObject:[NSString stringWithUTF8String: item.c_str()]];
    });
    [[HStoreIOS getInstance] requestProductData:set andDelegate:delegate];
}

void HStoreImplIOS::cancelLoadProducts() {
    [[HStoreIOS getInstance] cancelRequestProductData];
}

bool HStoreImplIOS::isProductLoaded(const char *productId) const {
    if (!productId) {
        return false;
    }
    return [[HStoreIOS getInstance] isProductLoaded:[NSString stringWithUTF8String:productId]];
}

bool HStoreImplIOS::purchase(const char *productId, int count) {
    if (!productId) {
        return false;
    }
    SKProduct *product = [[HStoreIOS getInstance] getProduct:[NSString stringWithUTF8String:productId]];
    if (product) {
        [[HStoreIOS getInstance] purchase:product withCount:count];
        return true;
    }
    return false;
}

void HStoreImplIOS::finishTransaction(HStorePaymentTransaction *transaction) {
    auto data = transaction->getTransactionData();
    [[HStoreIOS getInstance] finishTransaction:static_cast<SKPaymentTransaction*>(data)];
    auto it = _transactions.find(transaction->getTransactionIdentifier());
    if (it != _transactions.end()) {
        it->second->release();
        _transactions.erase(it);
    }
}

HStorePaymentTransaction::ReceiptVerifyMode HStoreImplIOS::getReceiptVerifyMode() const {
    return [HStoreIOS getInstance].receiptVerifyMode;
}

void HStoreImplIOS::setReceiptVerifyMode(HStorePaymentTransaction::ReceiptVerifyMode mode, bool isSandbox) {
    HStoreIOS *store = [HStoreIOS getInstance];
    store.receiptVerifyMode = mode;
    store.isSandbox = isSandbox;
}

const char* HStoreImplIOS::getReceiptVerifyServerUrl() const {
    return [[HStoreIOS getInstance].receiptVerifyServerUrl cStringUsingEncoding:NSUTF8StringEncoding];
}

void HStoreImplIOS::setReceiptVerifyServerUrl(const char *url) {
    [HStoreIOS getInstance].receiptVerifyServerUrl = [NSString stringWithUTF8String:url];
}

#pragma mark - delegates

void HStoreImplIOS::onTransactionCompleted(HStorePaymentTransaction *transaction) {
    _transactions[transaction->getTransactionIdentifier()] = transaction;
    transaction->retain();

    if (_delegate) {
        _delegate->onTransactionCompleted(transaction);
    }
}

void HStoreImplIOS::onTransactionFailed(HStorePaymentTransaction *transaction, int errorCode, const char *errorString) {
    _transactions[transaction->getTransactionIdentifier()] = transaction;
    transaction->retain();

    if (_delegate) {
        _delegate->onTransactionFailed(transaction, errorCode, errorString);
    }
}

void HStoreImplIOS::onTransactionRestored(HStorePaymentTransaction *transaction) {
    _transactions[transaction->getTransactionIdentifier()] = transaction;
    transaction->retain();

    if (_delegate) {
        _delegate->onTransactionRestored(transaction);
    }
}

void HStoreImplIOS::onRestoreCompletedTransactionsFailed(int errorCode, const char *errorString) {
    if (_delegate) {
        _delegate->onRestoreCompletedTransactionsFailed(errorCode, errorString);
    }
}

void HStoreImplIOS::onRestoreCompletedTransactionsFinished() {
    if (_delegate) {
        _delegate->onRestoreCompletedTransactionsFinished();
    }
}

NS_CC_H_END
