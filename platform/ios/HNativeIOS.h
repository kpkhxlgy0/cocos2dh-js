#ifndef  __PLATFORM_IOS_HNATIVEIOS__
#define  __PLATFORM_IOS_HNATIVEIOS__

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#include "../../helper/native/HAlertViewDelegate.h"

@interface CCNativeIOS : NSObject < UIAlertViewDelegate >
{
    UIActivityIndicatorView *activityIndicatorView_;
    
    UIAlertView *alertView_;
    cocos2d::h::HAlertViewDelegate *alertViewDelegates_;
#if CC_LUA_ENGINE_ENABLED > 0
    LUA_FUNCTION alertViewLuaListener_;
#endif
}

+ (CCNativeIOS *)sharedInstance;


#pragma mark -
#pragma mark activity indicator

- (void)showActivityIndicator:(UIActivityIndicatorViewStyle)style;
- (void)hideActivityIndicator;


#pragma mark -
#pragma mark alert view

- (void)createAlertView:(NSString *)title
             andMessage:(NSString *)message
   andCancelButtonTitle:(NSString *)cancelButtonTitle;
- (NSInteger)addAlertButton:(NSString *)buttonTitle;
- (void)showAlertViewWithDelegate:(cocos2d::h::HAlertViewDelegate *)delegate;
- (void)removeAlertView;
- (void)cancelAlertView;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
- (void)showAlertViewWithObjcDelegate:(id<UIAlertViewDelegate>)delegate;
#endif

#pragma mark -
#pragma mark UIAlertView delegates

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;

@end

#endif // __PLATFORM_IOS_HNATIVEIOS__
