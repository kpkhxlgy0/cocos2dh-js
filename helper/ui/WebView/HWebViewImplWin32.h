#ifndef __HWebViewImplWin32_H__
#define __HWebViewImplWin32_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "Cocos2dxhMacros.h"
#include "HWebViewImpl.h"

NS_CC_H_BEGIN

class HWebViewImplWin32 : public HWebViewImpl {
public:
    HWebViewImplWin32(HWebView* INwebView);
    virtual ~HWebViewImplWin32();
    bool initWithSize(const CCSize& INsize);
    
    void setPosition(const CCPoint& pos);
    void setVisible(bool visible);
    void setContentSize(const CCSize& size);
    void setAnchorPoint(const CCPoint& anchorPoint);
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
    CCSize          m_tContentSize;
    CCPoint         m_obPosition;
    CCPoint         m_obAnchorPoint;
    void*           m_systemControl;
};

NS_CC_H_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#endif // __HWebViewImplWin32_H__

