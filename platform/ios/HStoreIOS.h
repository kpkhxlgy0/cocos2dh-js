#ifndef  __PLATFORM_IOS_HSTOREIOS__
#define  __PLATFORM_IOS_HSTOREIOS__

#import <StoreKit/StoreKit.h>

#import "HStore.h"

class HStoreReceiptVerifyRequestIOS;

@interface HStoreIOS : NSObject < SKPaymentTransactionObserver, SKProductsRequestDelegate >
{
    bool _isSandbox;
    cocos2d::h::HStorePaymentTransaction::ReceiptVerifyMode _receiptVerifyMode;
    NSString *_receiptVerifyServerUrl;

    cocos2d::h::HStoreTransactionDelegate *_transactionDelegate;
    cocos2d::h::HStoreProductsRequestDelegate *_productRequestDelegate;
    NSMutableDictionary *_loadedProducts;
    SKProductsRequest *_productRequest;
}

@property (nonatomic, assign) bool isSandbox;
@property (nonatomic, assign) cocos2d::h::HStorePaymentTransaction::ReceiptVerifyMode receiptVerifyMode;
@property (nonatomic, retain) NSString *receiptVerifyServerUrl;

#pragma mark - init

+ (HStoreIOS *)getInstance;
+ (void)destroyInstance;
- (id)init;
- (void)setDelegate:(cocos2d::h::HStoreTransactionDelegate *)delegate;

#pragma mark - Making a Purchase

- (BOOL)canMakePurchases;
- (void)restoreCompletedTransactions;
- (void)purchase:(SKProduct *)product withCount:(int)count;
- (void)finishTransaction:(SKPaymentTransaction *)transaction;

#pragma mark - Retrieving Product Information

- (void)requestProductData:(NSSet *)productsId andDelegate:(cocos2d::h::HStoreProductsRequestDelegate *)delegate;

- (void)cancelRequestProductData;
- (BOOL)isProductLoaded:(NSString *)productId;
- (SKProduct *)getProduct:(NSString *)productId;
- (void)cleanCachedProducts;

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error;

#pragma mark -
#pragma mark Handling Transactions

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
- (void)transactionCompleted:(SKPaymentTransaction *)transaction
    andReceiptVerifyStatus:(cocos2d::h::HStorePaymentTransaction::ReceiptVerifyStatus)receiptVerifyStatus;
- (void)transactionFailed:(SKPaymentTransaction *)transaction
    andReceiptVerifyStatus:(cocos2d::h::HStorePaymentTransaction::ReceiptVerifyStatus)receiptVerifyStatus;
- (void)transactionRestored:(SKPaymentTransaction *)transaction
    andReceiptVerifyStatus:(cocos2d::h::HStorePaymentTransaction::ReceiptVerifyStatus)receiptVerifyStatus;

#pragma mark - Verifying Store Receipts

- (void)verifyTransactionReceipt:(SKPaymentTransaction *)transaction withType:(BOOL)isRestored;
- (void)verifyReceiptRequestFinished:(HStoreReceiptVerifyRequestIOS *)handler withType:(BOOL)isRestored;
- (void)verifyReceiptRequestFailed:(HStoreReceiptVerifyRequestIOS *)handler withType:(BOOL)isRestored;

#pragma mark - helper

- (cocos2d::h::HStorePaymentTransaction *)create:(SKPaymentTransaction *)transaction
    andReceiptVerifyStatus:(cocos2d::h::HStorePaymentTransaction::ReceiptVerifyStatus)receiptVerifyStatus;

@end

#endif // __PLATFORM_IOS_HSTOREIOS__
