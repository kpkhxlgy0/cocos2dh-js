
#include "HStoreImplWin32.h"

// #import "HStoreIOS.h"
#ifdef COCOS2D_LUA
#include "CCLuaEngine.h"
#endif // COCOS2D_LUA

NS_CC_H_BEGIN

HStoreImpl* __createHStoreImpl() {
    return new HStoreImplWin32();
}

HStoreImplWin32::~HStoreImplWin32()
{
#ifdef COCOS2D_LUA
    unregisterStoreScriptHandler();
#endif // COCOS2D_LUA
//     [CCStoreIOS purgeSharedStore];
}

void HStoreImplWin32::postInitWithTransactionObserver(CCStoreTransactionObserver* observer)
{
    m_observer = observer;
//     [[CCStoreIOS sharedStore] postInitWithTransactionObserver:this];
}

#ifdef COCOS2D_LUA
void HStoreImplWin32::registerStoreScriptHandler(int INhandler) {
    unregisterStoreScriptHandler();
    m_storeScriptHandler = INhandler;
    LUALOG("[LUA] Add HStore script handler: %d", m_storeScriptHandler);
}

void HStoreImplWin32::unregisterStoreScriptHandler() {
    if (m_storeScriptHandler) {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_storeScriptHandler);
        LUALOG("[LUA] Remove HStore script handler: %d", m_storeScriptHandler);
        m_storeScriptHandler = 0;
    }
}

void HStoreImplWin32::handleScriptStoreCompleted(CCStorePaymentTransaction* transaction) {
#ifdef COCOS2D_LUA
    if (!m_storeScriptHandler) {
        return;
    }
    CCLuaEngine *luaEngine = (CCLuaEngine*)CCScriptEngineManager::sharedManager()->getScriptEngine();
    CCLuaStack *stack = luaEngine->getLuaStack();
    stack->pushString("completed");
    stack->pushCCObject(transaction, "CCStorePaymentTransaction");
    stack->executeFunctionByHandler(m_storeScriptHandler, 2);
#endif // COCOS2D_LUA
}

void HStoreImplWin32::handleScriptStoreFailed(CCStorePaymentTransaction* transaction) {
#ifdef COCOS2D_LUA
    if (!m_storeScriptHandler) {
        return;
    }
    CCLuaEngine *luaEngine = (CCLuaEngine*)CCScriptEngineManager::sharedManager()->getScriptEngine();
    CCLuaStack *stack = luaEngine->getLuaStack();
    stack->pushString("failed");
    stack->pushCCObject(transaction, "CCStorePaymentTransaction");
    stack->executeFunctionByHandler(m_storeScriptHandler, 2);
#endif // COCOS2D_LUA
}

void HStoreImplWin32::handleScriptStoreRestored(CCStorePaymentTransaction* transaction) {
#ifdef COCOS2D_LUA
    if (!m_storeScriptHandler) {
        return;
    }
    CCLuaEngine *luaEngine = (CCLuaEngine*)CCScriptEngineManager::sharedManager()->getScriptEngine();
    CCLuaStack *stack = luaEngine->getLuaStack();
    stack->pushString("restored");
    stack->pushCCObject(transaction, "CCStorePaymentTransaction");
    stack->executeFunctionByHandler(m_storeScriptHandler, 2);
#endif // COCOS2D_LUA
}
#endif // COCOS2D_LUA

bool HStoreImplWin32::canMakePurchases(void)
{
//     return [[CCStoreIOS sharedStore] canMakePurchases];
    return false;
}

void HStoreImplWin32::loadProducts(CCArray* productsId, CCStoreProductsRequestDelegate* delegate)
{
//     NSMutableSet* set = [NSMutableSet set];
//     for (int i = 0; i < productsId->count(); ++i)
//     {
//         CCString* productId = static_cast<CCString*>(productsId->objectAtIndex(i));
//         [set addObject:[NSString stringWithUTF8String: productId->m_sString.c_str()]];
//     }
//     [[CCStoreIOS sharedStore] requestProductData:set andDelegate:delegate];
}

#ifdef COCOS2D_LUA
void HStoreImplWin32::loadProducts(cocos2d::CCArray *productsId, int INhandler) {
    
}
#endif // COCOS2D_LUA

void HStoreImplWin32::cancelLoadProducts(void)
{
//     [[CCStoreIOS sharedStore] cancelRequestProductData];
}

bool HStoreImplWin32::isProductLoaded(const char* productId)
{
//     if (!productId) return false;
//     return [[CCStoreIOS sharedStore] isProductLoaded:[NSString stringWithUTF8String:productId]];
    return false;
}

bool HStoreImplWin32::purchase(const char* productId)
{
//     if (!productId) return false;
//     SKProduct *product = [[CCStoreIOS sharedStore] getProduct:[NSString stringWithUTF8String:productId]];
//     if (product)
//     {
//         [[CCStoreIOS sharedStore] purchase:product];
//         return true;
//     }
    return false;
}

void HStoreImplWin32::finishTransaction(CCStorePaymentTransaction *transaction)
{
//     CCStorePaymentTransactionWrapper* wrapper = transaction->getTransactionWrapper();
//     [[CCStoreIOS sharedStore] finishTransaction:(SKPaymentTransaction *)wrapper->getTransactionObj()];
//     CCStorePaymentTransactionsIterator it = m_transactions.find(transaction->getTransactionIdentifier());
//     if (it != m_transactions.end())
//     {
//         it->second->release();
//         m_transactions.erase(it);
//     }
}

CCStoreReceiptVerifyMode HStoreImplWin32::getReceiptVerifyMode(void)
{
//     return [CCStoreIOS sharedStore].receiptVerifyMode;
    return CCStoreReceiptVerifyModeNone;
}

void HStoreImplWin32::setReceiptVerifyMode(CCStoreReceiptVerifyMode mode, CCStoreIsSandbox isSandbox)
{
//     [CCStoreIOS sharedStore].receiptVerifyMode = mode;
//     [CCStoreIOS sharedStore].isSandbox = isSandbox;
}

const char* HStoreImplWin32::getReceiptVerifyServerUrl(void)
{
//     return [[CCStoreIOS sharedStore].receiptVerifyServerUrl cStringUsingEncoding:NSUTF8StringEncoding];
    return NULL;
}

void HStoreImplWin32::setReceiptVerifyServerUrl(const char* url)
{
//     [CCStoreIOS sharedStore].receiptVerifyServerUrl = [NSString stringWithUTF8String:url];
}

const char* HStoreImplWin32::getUserAccount() {
//     return m_userAccount.c_str();
    return NULL;
}

void HStoreImplWin32::setUserAccount(const char *INaccount) {
//     m_userAccount = INaccount;
}

const char* HStoreImplWin32::getPostHeaderName() {
//     return m_postHeaderName.c_str();
    return NULL;
}

void HStoreImplWin32::setPostHeaderName(const char *INheaderName) {
//     m_postHeaderName = INheaderName;
}

const char* HStoreImplWin32::getStatusHeaderKey() {
//     return m_statusHeaderKey.c_str();
    return NULL;
}

void HStoreImplWin32::setStatusHeaderKey(const char *INkey) {
//     m_statusHeaderKey = INkey;
}

const char* HStoreImplWin32::getSuccessHeaderValue() {
//     return m_successHeaderValue.c_str();
    return NULL;
}

void HStoreImplWin32::setSuccessHeaderValue(const char *INvalue) {
//     m_successHeaderValue = INvalue;
}

#pragma mark -
#pragma mark delegates

void HStoreImplWin32::transactionCompleted(CCStorePaymentTransaction* transaction)
{
//     m_transactions[transaction->getTransactionIdentifier()] = transaction;
//     transaction->retain();
// 
//     if (m_observer)
//     {
//         m_observer->transactionCompleted(transaction);
//     }
#ifdef COCOS2D_LUA
    handleScriptStoreCompleted(transaction);
#endif // COCOS2D_LUA
}

void HStoreImplWin32::transactionFailed(CCStorePaymentTransaction* transaction)
{
//     m_transactions[transaction->getTransactionIdentifier()] = transaction;
//     transaction->retain();
// 
//     if (m_observer)
//     {
//         m_observer->transactionFailed(transaction);
//     }
#ifdef COCOS2D_LUA
    handleScriptStoreFailed(transaction);
#endif // COCOS2D_LUA
}

void HStoreImplWin32::transactionRestored(CCStorePaymentTransaction* transaction)
{
//     m_transactions[transaction->getTransactionIdentifier()] = transaction;
//     transaction->retain();
// 
//     if (m_observer)
//     {
//         m_observer->transactionRestored(transaction);
//     }
#ifdef COCOS2D_LUA
    handleScriptStoreRestored(transaction);
#endif // COCOS2D_LUA
}

NS_CC_H_END
