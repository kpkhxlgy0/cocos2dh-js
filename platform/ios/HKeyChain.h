//
//  HKeyChain.h
//  cocos2dxh
//
//  Created by XiaoLongHan on 12/23/13.
//
//

#import <UIKit/UIKit.h>
#import <Security/Security.h>

#define DEFAULT_SECATTRLABEL            @"Item label"
#define DEFAULT_SECSECATTRDESCRIPTION   @"Item description"
#define DEFAULT_SECATTRACCOUNT          @"Account"
#define DEFAULT_SECATTRSERVICE          @"Service"
#define DEFAULT_SECATTRCOMMENT          @"Your comment here."
#define DEFAULT_SECVALUEDATA            @"password"

//Define an Objective-C wrapper class to hold Keychain Services code.
@interface KeychainWrapper : NSObject {
    NSMutableDictionary        *keychainData;
    NSMutableDictionary        *genericPasswordQuery;
    UInt8 *_keychainItemIdentifier;
}

@property (nonatomic, strong) NSMutableDictionary *keychainData;
@property (nonatomic, strong) NSMutableDictionary *genericPasswordQuery;

- (id)initWithIdentifier:(NSString*)ident;
- (void)mySetObject:(id)inObject forKey:(id)key;
- (id)myObjectForKey:(id)key;
- (void)resetKeychainItem;

@end
