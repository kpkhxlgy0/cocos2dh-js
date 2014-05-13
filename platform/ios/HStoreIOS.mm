
#import "HStoreIOS.h"
#import "HStoreReceiptVerifyRequestIOS.h"
//#import "json/SBJSON.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include "../../helper/crypto/HCrypto.h"
#include <string>

#ifndef utf8cstr
#define utf8cstr(nsstr) (nsstr ? [nsstr cStringUsingEncoding:NSUTF8StringEncoding] : "")
#endif

USING_NS_CC;
USING_NS_CC_H;
using namespace std;

@implementation HStoreIOS

static HStoreIOS *s_sharedStore = nil;
static const char* const APPSTORE_RECEIPT_VERIFY_URL = "https://buy.itunes.apple.com/verifyReceipt";
static const char* const SANDBOX_RECEIPT_VERIFY_URL = "https://sandbox.itunes.apple.com/verifyReceipt";

@synthesize isSandbox = _isSandbox;
@synthesize receiptVerifyMode = _receiptVerifyMode;
@synthesize receiptVerifyServerUrl = _receiptVerifyServerUrl;

#pragma mark - init

+ (HStoreIOS *)getInstance {
    if (!s_sharedStore) {
        s_sharedStore = [[HStoreIOS alloc] init];
    }
    return s_sharedStore;
}

+ (void) destroyInstance {
    if (s_sharedStore) {
        [s_sharedStore release];
        s_sharedStore = nil;
    }
}

- (id)init {
    if (self = [super init]) {
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        _loadedProducts = [NSMutableDictionary dictionaryWithCapacity:50];
        [_loadedProducts retain];
        _receiptVerifyMode = HStorePaymentTransaction::ReceiptVerifyMode::None;
    }
    return self;
}

- (void)dealloc {
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    [_loadedProducts release];
    [_productRequest release];
    [super dealloc];
}

- (void)setDelegate:(HStoreTransactionDelegate *)delegate {
    _transactionDelegate = delegate;
}

#pragma mark - Making a Purchase

- (BOOL)canMakePurchases {
    return [SKPaymentQueue canMakePayments];
}

- (void)restoreCompletedTransactions {
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

- (void)purchase:(SKProduct *)product withCount:(int)count {
    CCLOG("[CCStore_obj] purchase() pid: %s", utf8cstr(product.productIdentifier));
    SKMutablePayment *payment = [SKMutablePayment paymentWithProduct:product];
    payment.quantity = count;
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}

- (void)finishTransaction:(SKPaymentTransaction *)transaction {
    CCLOG("[CCStore_obj] finishTransaction() tid: %s",  utf8cstr(transaction.transactionIdentifier));
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}

#pragma mark - Retrieving Product Information

- (void) requestProductData:(NSSet *)productsId andDelegate:(cocos2d::h::HStoreProductsRequestDelegate *)delegate {
    if (_productRequest) {
        delegate->onRequestProductsFailed(HStore::ProductRequestError::PreviousRequestNotCompleted,
                                          "StoreProductsRequestErrorPreviousRequestNotCompleted");
        return;
    }
    
    _productRequestDelegate = delegate;
    SKProductsRequest *request = [[SKProductsRequest alloc] initWithProductIdentifiers:productsId];
    request.delegate = self;
    [request autorelease];
    [request start];
    _productRequest = request;
}

- (void)cancelRequestProductData {
    if (_productRequest) {
        [_productRequest cancel];
        _productRequest = nil;
        if (_productRequestDelegate) {
            _productRequestDelegate->onRequestProductsFailed(HStore::ProductRequestError::Cancelled,
                                                             "StoreProductsRequestErrorCancelled");
        }
        _productRequestDelegate = nullptr;
    }
}

- (BOOL)isProductLoaded:(NSString *)productId {
    return [_loadedProducts objectForKey:productId] != nil;
}

- (SKProduct *)getProduct:(NSString *)productId {
    return [_loadedProducts objectForKey:productId];
}

- (void)cleanCachedProducts {
    [_loadedProducts removeAllObjects];
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
    vector<HStoreProduct*> products;
    for (int i = 0; i < response.products.count; ++i) {
        // cache loaded product
        SKProduct* product = [response.products objectAtIndex:i];
        [_loadedProducts setObject:product forKey:product.productIdentifier];
        
        // convert SKProduct to CCStoreProduct
        auto ccproduct = HStoreProduct::create(utf8cstr(product.productIdentifier),
                                               utf8cstr(product.localizedTitle),
                                               utf8cstr(product.localizedDescription),
                                               [product.price floatValue],
                                               utf8cstr(product.priceLocale.localeIdentifier));
        products.push_back(ccproduct);
        CCLOG("[CCStore_obj] productsRequestDidReceiveResponse() get pid: %s", utf8cstr(product.productIdentifier));
    }
    
    vector<string> invalidProductsId;
    for (int i = 0; i < response.invalidProductIdentifiers.count; ++i) {
        NSString* productId = [response.invalidProductIdentifiers objectAtIndex:i];
        invalidProductsId.push_back(utf8cstr(productId));
        CCLOG("[CCStore_obj] productsRequestDidReceiveResponse() invalid pid: %s", utf8cstr(productId));
    }
    
    request.delegate = nil;
    _productRequest = nil;
    if (_productRequestDelegate) {
        _productRequestDelegate->onRequestProductsCompleted(products, invalidProductsId);
        _productRequestDelegate = nullptr;
    }
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error {
    request.delegate = nil;
    _productRequest = nil;
    auto code = static_cast<HStore::ProductRequestError>(error.code);
    if (_productRequestDelegate) {
        _productRequestDelegate->onRequestProductsFailed(code, utf8cstr(error.localizedDescription));
        if (code != HStore::ProductRequestError::PreviousRequestNotCompleted) {
            _productRequestDelegate = nullptr;
        }
    }
}

#pragma mark - Handling Transactions

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
    for (int i = 0; i < [transactions count]; ++i) {
        SKPaymentTransaction *transaction = [transactions objectAtIndex:i];
        if (transaction.transactionState != SKPaymentTransactionStatePurchasing) {
            CCLOG("[CCStore_obj] paymentQueueUpdatedTransactions() tid: %s",
                  utf8cstr(transaction.transactionIdentifier));
        }
        
        switch (transaction.transactionState) {
            case SKPaymentTransactionStatePurchased: {
                CCLOG("transaction '%s' SKPaymentTransactionStatePurchased", utf8cstr(transaction.transactionIdentifier));
                if (_receiptVerifyMode != HStorePaymentTransaction::ReceiptVerifyMode::None) {
                    [self verifyTransactionReceipt:transaction withType:NO];
                } else {
                    [self transactionCompleted:transaction andReceiptVerifyStatus:HStorePaymentTransaction::ReceiptVerifyStatus::None];
                }
                break;
            }
            case SKPaymentTransactionStateFailed: {
                CCLOG("transaction '%s' SKPaymentTransactionStateFailed", utf8cstr(transaction.transactionIdentifier));
                NSError *error = transaction.error;
                if (error.code == 2) {
                    CCLOG("error: %d - %s", error.code, "cancel");
                } else {
                    CCLOG("error: %d - %s", error.code, utf8cstr([transaction.error localizedDescription]));
                }
                [self transactionFailed:transaction andReceiptVerifyStatus:HStorePaymentTransaction::ReceiptVerifyStatus::None];
                break;
            }
            case SKPaymentTransactionStateRestored: {
                CCLOG("transaction '%s' SKPaymentTransactionStateRestored", utf8cstr(transaction.transactionIdentifier));
                if (_receiptVerifyMode != HStorePaymentTransaction::ReceiptVerifyMode::None) {
                    [self verifyTransactionReceipt:transaction withType:YES];
                } else {
                    [self transactionRestored:transaction andReceiptVerifyStatus:HStorePaymentTransaction::ReceiptVerifyStatus::None];
                }
                break;
            }
        }
    }
}
- (void)transactionCompleted:(SKPaymentTransaction *)transaction
      andReceiptVerifyStatus:(HStorePaymentTransaction::ReceiptVerifyStatus)receiptVerifyStatus {
    _transactionDelegate->onTransactionCompleted([self create:transaction
                                       andReceiptVerifyStatus:receiptVerifyStatus]);
}

- (void)transactionFailed:(SKPaymentTransaction *)transaction
   andReceiptVerifyStatus:(HStorePaymentTransaction::ReceiptVerifyStatus)receiptVerifyStatus
{
    NSError *error = transaction.error;
    _transactionDelegate->onTransactionFailed([self create:transaction
                                    andReceiptVerifyStatus:receiptVerifyStatus],
                                              error.code,
                                              utf8cstr(error.localizedDescription));
}

- (void)transactionRestored:(SKPaymentTransaction *)transaction
     andReceiptVerifyStatus:(HStorePaymentTransaction::ReceiptVerifyStatus)receiptVerifyStatus;
{
    _transactionDelegate->onTransactionRestored([self create:transaction
                                      andReceiptVerifyStatus:receiptVerifyStatus]);
}

- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error {
    if (error.code == 2) {
        CCLOG("restoreCompletedTransactionsFailedWithError: %d - %s", error.code, "cancel");
    } else {
        CCLOG("restoreCompletedTransactionsFailedWithError: %d - %s", error.code, utf8cstr(error.localizedDescription));
    }
    _transactionDelegate->onRestoreCompletedTransactionsFailed(error.code,
                                                               utf8cstr(error.localizedDescription));
}

- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue {
    CCLOG("paymentQueueRestoreCompletedTransactionsFinished");
    _transactionDelegate->onRestoreCompletedTransactionsFinished();
}

#pragma mark - Verifying Store Receipts

- (void)verifyTransactionReceipt:(SKPaymentTransaction *)transaction withType:(BOOL)isRestored
{
    if (transaction.transactionState != SKPaymentTransactionStatePurchased) return;
    
    CCLOG("[CCStore_obj] verifyTransactionReceipt() tid: %s", utf8cstr(transaction.transactionIdentifier));
    
    // convert receipt to JSON string
    int length = [transaction.transactionReceipt length];
    auto str = HCrypto::encodeBase64([transaction.transactionReceipt bytes], length);
    if (str.length() == 0) {
        if (isRestored) {
            [self transactionRestored:transaction andReceiptVerifyStatus:HStorePaymentTransaction::ReceiptVerifyStatus::UnknownError];
        } else {
            [self transactionCompleted:transaction andReceiptVerifyStatus:HStorePaymentTransaction::ReceiptVerifyStatus::UnknownError];
        }
        return;
    }
    
    const char *url;
    if (_receiptVerifyMode == HStorePaymentTransaction::ReceiptVerifyMode::Server) {
        url = [_receiptVerifyServerUrl UTF8String];
        
        rapidjson::Document postValue;
        postValue.SetObject();
        auto allocPost = postValue.GetAllocator();
        
        rapidjson::Value rootValue;
        rootValue.SetObject();
        rapidjson::Value receiptData;
        receiptData.SetString(str.c_str(), str.length(), allocPost);
        rootValue.AddMember("receipt-data", receiptData, allocPost);
        
        postValue.AddMember("receipt", rootValue, allocPost);
        rapidjson::Value isSandbox;
        isSandbox.SetBool(_isSandbox);
        postValue.AddMember("isSandbox", isSandbox, allocPost);
        rapidjson::Value userAccount;
        userAccount.SetString(HStore::getInstance()->getUserAccount().c_str(), allocPost);
        postValue.AddMember("userAccount", userAccount, allocPost);
        
        rapidjson::StringBuffer strBuffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(strBuffer);
        rootValue.Accept(writer);
        str = strBuffer.GetString();
    } else {
        url = _isSandbox ? SANDBOX_RECEIPT_VERIFY_URL : APPSTORE_RECEIPT_VERIFY_URL;
        
        rapidjson::Document rootValue;
        rootValue.SetObject();
        rapidjson::Document::AllocatorType &alloc = rootValue.GetAllocator();
        rapidjson::Value receiptData;
        receiptData.SetString(str.c_str(), str.length(), alloc);
        rootValue.AddMember("receipt-data", receiptData, alloc);
        
        rapidjson::StringBuffer strBuffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(strBuffer);
        rootValue.Accept(writer);
        str = strBuffer.GetString();
    }
    
    // create request
    auto handler = HStoreReceiptVerifyRequestIOS::create(self, transaction, url, isRestored);
    auto headers = handler->getRequest()->getHeaders();
    headers.push_back("Content-Type: application/json;charset=utf-8");
    handler->getRequest()->setHeaders(headers);
    handler->getRequest()->setRequestData(str.data(), str.length());
//    CCLOG("%s", str.c_str());
    network::HttpClient::getInstance()->send(handler->getRequest());
}

- (void)verifyReceiptRequestFinished:(HStoreReceiptVerifyRequestIOS *)handler withType:(BOOL)isRestored
{
    auto transaction = handler->getTransaction();
    auto response = handler->getResponse()->getResponseData();
    const string responseString(&response->front(), response->size());
    
    CCLOG("[CCStore_obj] verify receipt finished, pid: %s\n  response:\n%s\n\n",
          utf8cstr(transaction.payment.productIdentifier),
          responseString.c_str());
    
    rapidjson::Document rootValue;
    rootValue.Parse<0>(responseString.c_str());
    
    // check result
    if (rootValue.IsNull() || !rootValue.HasMember("status") || !rootValue["status"].IsInt()) {
        // invalid JSON string
        [self transactionFailed:transaction andReceiptVerifyStatus:HStorePaymentTransaction::ReceiptVerifyStatus::InvalidResult];
    } else {
        auto status = rootValue["status"].IsInt();
        if (status == 0) {
            // status is ok, do more checks
            BOOL isValidReceipt = NO;
            do {
                if (!rootValue.HasMember("receipt")) {
                    break;
                }
                const auto &receiptData = rootValue["receipt"];
                auto transactionId = receiptData["transaction_id"].GetString();
                if ([transaction.transactionIdentifier compare:[NSString stringWithUTF8String:transactionId]] != NSOrderedSame) {
                    // check failed
                    break;
                }
                auto productIdentifier = receiptData["product_id"].GetString();
                if ([transaction.payment.productIdentifier compare:[NSString stringWithUTF8String:productIdentifier]] != NSOrderedSame) {
                    break;
                }
                
                // receipt is valid
                isValidReceipt = YES;
            } while (0);
            
            if (isValidReceipt) {
                if (isRestored) {
                    [self transactionRestored:transaction
                        andReceiptVerifyStatus:HStorePaymentTransaction::ReceiptVerifyStatus::OK];
                } else {
                    [self transactionCompleted:transaction
                        andReceiptVerifyStatus:HStorePaymentTransaction::ReceiptVerifyStatus::OK];
                }
            } else {
                [self transactionFailed:transaction
                 andReceiptVerifyStatus:HStorePaymentTransaction::ReceiptVerifyStatus::InvalidReceipt];
            }
        } else {
            [self transactionFailed:transaction
                andReceiptVerifyStatus:static_cast<HStorePaymentTransaction::ReceiptVerifyStatus>(status)];
        }
    }
}

- (void)verifyReceiptRequestFailed:(HStoreReceiptVerifyRequestIOS *)handler withType:(BOOL)isRestored
{
    SKPaymentTransaction* transaction = handler->getTransaction();
    const std::string reqString(handler->getRequest()->getRequestData(), handler->getRequest()->getRequestDataSize());
    
    CCLOG("[CCStore_obj] WARN, verify receipt failed(), pid: %s\n  request:\n%s\n\n",
          utf8cstr(transaction.payment.productIdentifier),
          reqString.c_str());
    
    [self transactionFailed:transaction andReceiptVerifyStatus:HStorePaymentTransaction::ReceiptVerifyStatus::RequestFailed];
}

#pragma mark - helper

- (cocos2d::h::HStorePaymentTransaction *)create:(SKPaymentTransaction *)transaction
    andReceiptVerifyStatus:(HStorePaymentTransaction::ReceiptVerifyStatus)receiptVerifyStatus {
    const char *ccid        = utf8cstr(transaction.transactionIdentifier);
    const char *ccproductId = utf8cstr(transaction.payment.productIdentifier);
    int quantity            = transaction.payment.quantity;
    double dateTime         = [transaction.transactionDate timeIntervalSince1970];
    int receiptDataLength   = 0;
    const void *receiptData = nullptr;
    int errorCode           = 0;
    const char *errorDescription = "";
    
    auto state = HStorePaymentTransaction::State::Null;
    switch (transaction.transactionState) {
        case SKPaymentTransactionStateFailed:
            errorCode = transaction.error.code;
            if (errorCode == SKErrorPaymentCancelled) {
                state = HStorePaymentTransaction::State::Cancelled;
            } else {
                state = HStorePaymentTransaction::State::Failed;
            }
            errorDescription = utf8cstr(transaction.error.localizedDescription);
            break;
        case SKPaymentTransactionStatePurchased:
            state = HStorePaymentTransaction::State::Purchased;
            receiptDataLength = transaction.transactionReceipt.length;
            receiptData = transaction.transactionReceipt.bytes;
            break;
        case SKPaymentTransactionStatePurchasing:
            state = HStorePaymentTransaction::State::Purchasing;
            break;
        case SKPaymentTransactionStateRestored:
            state = HStorePaymentTransaction::State::Restored;
    }
    
    if (transaction.originalTransaction)
    {
        auto originalTransaction = [self create:transaction.originalTransaction
                      andReceiptVerifyStatus:HStorePaymentTransaction::ReceiptVerifyStatus::None];
        return HStorePaymentTransaction::create(transaction,
                                                state,
                                                ccid,
                                                ccproductId,
                                                quantity,
                                                dateTime,
                                                receiptDataLength,
                                                receiptData,
                                                errorCode,
                                                errorDescription,
                                                originalTransaction,
                                                _receiptVerifyMode,
                                                receiptVerifyStatus);
    } else {
        return HStorePaymentTransaction::create(transaction,
                                                state,
                                                ccid,
                                                ccproductId,
                                                quantity,
                                                dateTime,
                                                receiptDataLength,
                                                receiptData,
                                                errorCode,
                                                errorDescription,
                                                nullptr,
                                                _receiptVerifyMode,
                                                receiptVerifyStatus);
    }
}

@end
