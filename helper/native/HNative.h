#ifndef __HELPER_NATIVE_HNATIVE_H__
#define __HELPER_NATIVE_HNATIVE_H__

#include "HAlertViewDelegate.h"
#include <string>

NS_CC_H_BEGIN

class HNative {
public:
    
#pragma mark -
#pragma mark activity indicator
    
    /** @brief Show activity indicator */
    static void showActivityIndicator(void);
    
    /** @brief Hide activity indicator */
    static void hideActivityIndicator(void);
    
#pragma mark -
#pragma mark alert view
    
    /** @brief Create alert view */
    static void createAlert(const char* title,
                            const char* message,
                            const char* cancelButtonTitle);
    
    /** @brief Add button to alert view, return button index */
    static int addAlertButton(const char* buttonTitle);

    /** @brief Show alert view */
    static void showAlert(HAlertViewDelegate* delegate = nullptr);
    /** @brief Hide and remove alert view */
    static void cancelAlert(void);
    
#pragma mark -
#pragma mark OpenUDID
    
    /** @brief Get OpenUDID value */
    static const std::string getOpenUDID(void);
    
    static std::string generateUuid();
    
#pragma mark -
#pragma mark misc
    
    /** @brief Open a web page in the browser; create an email; or call a phone number. */
    static void openURL(const char* url);
    
	/** @brief Show alert view, and get user input */
    static const std::string getInputText(const char* title, const char* message, const char* defaultValue);
    
#pragma mark -
#pragma mark helper
    
    static const std::string getDeviceName(void);
    // android should add permission <uses-permission android:name="android.permission.VIBRATE" />
    static void vibrate();
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    static void showAlertObjc(void *delegate);
#endif

private:
    HNative(void) {}
};

NS_CC_H_END

#endif // __HELPER_NATIVE_HNATIVE_H__
