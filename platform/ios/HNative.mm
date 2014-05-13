#include "../../helper/native/HNative.h"
#import <UIKit/UIKit.h>
#import "HNativeIOS.h"
#import "openudid/OpenUDIDIOS.h"
#import "AudioToolbox/AudioServices.h"
#include "cocos2d.h"
#include <uuid/uuid.h>
#include "../../helper/crypto/HCrypto.h"

#import "HKeyChain.h"

using namespace std;

NS_CC_H_BEGIN

#pragma mark - activity indicator

void HNative::showActivityIndicator(void)
{
    [[CCNativeIOS sharedInstance] showActivityIndicator:UIActivityIndicatorViewStyleWhiteLarge];
}

void HNative::hideActivityIndicator(void)
{
    [[CCNativeIOS sharedInstance] hideActivityIndicator];
}

#pragma mark - alert view

void HNative::createAlert(const char* title,
                           const char* message,
                           const char* cancelButtonTitle)
{
    NSString *title_ = [NSString stringWithUTF8String:title ? title : ""];
    NSString *message_ = [NSString stringWithUTF8String:message ? message : ""];
    NSString *cancelButtonTitle_ = cancelButtonTitle ? [NSString stringWithUTF8String:cancelButtonTitle] : nil;
    [[CCNativeIOS sharedInstance] createAlertView:title_
                                         andMessage:message_
                               andCancelButtonTitle:cancelButtonTitle_];
}

int HNative::addAlertButton(const char* buttonTitle)
{
    NSString *buttonTitle_ = [NSString stringWithUTF8String:buttonTitle ? buttonTitle : "Button"];
    return [[CCNativeIOS sharedInstance] addAlertButton:buttonTitle_];
}

void HNative::showAlert(HAlertViewDelegate* delegate)
{
    [[CCNativeIOS sharedInstance] showAlertViewWithDelegate:delegate];
}

void HNative::cancelAlert(void)
{
    [[CCNativeIOS sharedInstance] cancelAlertView];
}

void HNative::openURL(const char* url)
{
    if (!url) return;
    NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:url encoding:NSUTF8StringEncoding]];
    [[UIApplication sharedApplication] openURL:nsurl];
}

const string HNative::getInputText(const char* title, const char* message, const char* defaultValue)
{
    CCLOG("CCNative::getInputText() - not support this platform.");
    return string("");
}

#pragma mark - OpenUDID

const string HNative::getOpenUDID(void)
{
//#if TARGET_IPHONE_SIMULATOR
//    return string([[OpenUDIDIOS value] cStringUsingEncoding:NSUTF8StringEncoding]);
//#else
//    // @"com.apple.dts.KeychainUI"
//    KeychainWrapper *keychain = [[KeychainWrapper alloc] initWithIdentifier:[[NSBundle mainBundle] bundleIdentifier]];
//    NSString *str = [keychain myObjectForKey:(id)kSecAttrAccount];
//    if (!str || [str isEqualToString:DEFAULT_SECATTRACCOUNT]) {
//        str = [NSString stringWithUTF8String:generateUuid().c_str()];
//        [keychain mySetObject:str forKey:(id)kSecAttrAccount];
//    }
//    return string([str UTF8String]);
//#endif
    return string([[OpenUDIDIOS value] cStringUsingEncoding:NSUTF8StringEncoding]);
}

string HNative::generateUuid() {
    unsigned char a[16] = {0};
    uuid_generate(a);
    return HCrypto::bin2hex(a, 16);
}

const string HNative::getDeviceName(void)
{
    UIDevice *device = [UIDevice currentDevice];
    return [[device name] cStringUsingEncoding:NSUTF8StringEncoding];
}

void HNative::vibrate()
{
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void HNative::showAlertObjc(void *delegate)
{
    [[CCNativeIOS sharedInstance] showAlertViewWithObjcDelegate:(id<UIAlertViewDelegate>)delegate];
}
#endif

#if CC_LUA_ENGINE_ENABLED > 0
int CCNative::addAlertButtonLua(const char* buttonTitle)
{
    return addAlertButton(buttonTitle) + 1;
}

void CCNative::showAlertLua(cocos2d::LUA_FUNCTION listener)
{
    [[CCNativeIOS sharedInstance] showAlertViewWithLuaListener:listener];
}
#endif

NS_CC_H_END
