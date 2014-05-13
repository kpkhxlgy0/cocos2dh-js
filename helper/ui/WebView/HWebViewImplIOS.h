#ifndef __HWebViewImplIOS_H__
#define __HWebViewImplIOS_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Cocos2dxhMacros.h"
#include "HWebViewImpl.h"

#import <UIKit/UIKit.h>

@interface HUIWebView : NSObject <UIWebViewDelegate> {
@private
    UIWebView   *m_pUIWebView;
}

@property(nonatomic, assign) void* m_pWebViewImpl;

- (id)initWithFrame:(CGRect)INframeRect andWebView:(void *)INwebView;
- (void)setPosition:(CGPoint)INpoint;
- (void)setVisible:(BOOL)INvisible;
- (void)setContentSize:(CGSize)INsize;
- (void)onEnter;
- (void)onExit;

- (void)loadURL:(const char *)INurl;

- (void)stopLoading;
- (void)reload;

- (void)goBack;
- (void)goForward;

- (BOOL)canGoBack;
- (BOOL)canGoForward;
- (BOOL)isLoading;
@end

NS_CC_H_BEGIN

class HWebViewImplIOS : public HWebViewImpl {
public:
    HWebViewImplIOS(HWebView* INwebView);
    virtual ~HWebViewImplIOS();
    bool initWithSize(const Size& INsize);
    
    void setPosition(const Point& pos);
    void setVisible(bool visible);
    void setContentSize(const Size& size);
    void setAnchorPoint(const Point& anchorPoint);
    void visit(void);
    void onEnter(void);
    void onExit(void);
    
    void loadURL(const char* INurl);
    
    void stopLoading();
    void reload();
    
    void goBack();
    void goForward();
    
    bool canGoBack();
    bool canGoForward();
    bool isLoading();
private:
    void adjustTextFieldPosition();
private:
    Size          m_tContentSize;
    Point         m_obPosition;
    Point         m_obAnchorPoint;
    HUIWebView*     m_systemControl;
    bool            m_bInRetinaMode;
};

NS_CC_H_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif // __HWebViewImplIOS_H__

