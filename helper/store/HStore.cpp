#include "HStore.h"
#include "HStoreImpl.h"

using namespace std;

NS_CC_H_BEGIN

static HStore *s_sharedStore = nullptr;

HStore* HStore::getInstance() {
    if (!s_sharedStore) {
        s_sharedStore = new HStore();
        s_sharedStore->init();
    }
    return s_sharedStore;
}

void HStore::destroyInstance() {
    delete s_sharedStore;
    s_sharedStore = nullptr;
}

HStore::HStore()
: _storeImpl(nullptr)
, _delegateTransaction(nullptr)
, _delegateProduct(nullptr) {
    
}

HStore::~HStore() {
    delete _storeImpl;
    Ref *obj = dynamic_cast<Ref*>(_delegateTransaction);
    CC_SAFE_RELEASE(obj);
    obj = dynamic_cast<Ref*>(_delegateProduct);
    CC_SAFE_RELEASE(obj);
}

bool HStore::init(void) {
    _storeImpl = __createHStoreImpl();
    return true;
}

void HStore::setDelegate(HStoreTransactionDelegate *delegate) {
    Ref *obj = dynamic_cast<Ref*>(_delegateTransaction);
    CC_SAFE_RELEASE(obj);
    _delegateTransaction = delegate;
    obj = dynamic_cast<Ref*>(_delegateTransaction);
    CC_SAFE_RETAIN(obj);
    _storeImpl->setDelegate(_delegateTransaction);
}

bool HStore::canMakePurchases() const {
    return _storeImpl->canMakePurchases();
}

void HStore::restoreCompletedTransactions() {
    _storeImpl->restoreCompletedTransactions();
}

void HStore::loadProducts(const vector<string> &productsId, HStoreProductsRequestDelegate* delegate) {
    Ref *obj = dynamic_cast<Ref*>(_delegateProduct);
    CC_SAFE_RELEASE(obj);
    _delegateProduct = delegate;
    obj = dynamic_cast<Ref*>(_delegateProduct);
    CC_SAFE_RETAIN(obj);
    _storeImpl->loadProducts(productsId, delegate);
}

void HStore::cancelLoadProducts() {
    _storeImpl->cancelLoadProducts();
}

bool HStore::isProductLoaded(const char *productId) const {
    return _storeImpl->isProductLoaded(productId);
}

bool HStore::purchase(const char *productId, int count) {
    return _storeImpl->purchase(productId, count);
}

void HStore::finishTransaction(HStorePaymentTransaction *transaction) {
    _storeImpl->finishTransaction(transaction);
}

HStorePaymentTransaction::ReceiptVerifyMode HStore::getReceiptVerifyMode() const {
    return _storeImpl->getReceiptVerifyMode();
}

void HStore::setReceiptVerifyMode(HStorePaymentTransaction::ReceiptVerifyMode mode, bool isSandbox) {
    _storeImpl->setReceiptVerifyMode(mode, isSandbox);
}

const char* HStore::getReceiptVerifyServerUrl() const {
    return _storeImpl->getReceiptVerifyServerUrl();
}

void HStore::setReceiptVerifyServerUrl(const char *url) {
    _storeImpl->setReceiptVerifyServerUrl(url);
}

const std::string& HStore::getUserAccount() const {
    return _storeImpl->getUserAccount();
}

void HStore::setUserAccount(const std::string &account) {
    _storeImpl->setUserAccount(account);
}

NS_CC_H_END
