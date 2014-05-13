#ifndef __HWebViewImpl_H__
#define __HWebViewImpl_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"
#include "HWebView.h"

NS_CC_H_BEGIN

class HWebViewImpl {
	CC_SYNTHESIZE_READONLY(HWebView*, m_pWebView, WebView);
public:
    HWebViewImpl(HWebView* INwebView) : m_pWebView(INwebView),
	m_delegate(NULL) {
	}
    virtual ~HWebViewImpl() {
        CC_SAFE_RELEASE(dynamic_cast<Ref*>(m_delegate));
	}
    
    virtual bool initWithSize(const Size& size) = 0;
    
    virtual void setPosition(const Point& pos) = 0;
    virtual void setVisible(bool visible) = 0;
    virtual void setContentSize(const Size& size) = 0;
	virtual void setAnchorPoint(const Point& anchorPoint) = 0;
    virtual void visit(void) = 0;
    virtual void onEnter(void) = 0;
    virtual void onExit(void) = 0;
    
	virtual void loadURL(const char* INurl) = 0;
    
    virtual void stopLoading() = 0;
	virtual void reload() = 0;
    
	virtual void goBack() = 0;
	virtual void goForward() = 0;
    
	virtual bool canGoBack() = 0;
	virtual bool canGoForward() = 0;
    virtual bool isLoading() = 0;
    
    void setDelegate(HWebViewDelegate *INdelegate) {
        CC_SAFE_RELEASE(dynamic_cast<Ref*>(m_delegate));
        m_delegate = INdelegate;
        CC_SAFE_RETAIN(dynamic_cast<Ref*>(m_delegate));
    }
    HWebViewDelegate* getDelegate() { return m_delegate; }
private:
    HWebViewDelegate *m_delegate;
};

extern HWebViewImpl* createSystemWebView(HWebView* INwebView);

NS_CC_H_END

#endif // __HWebViewImpl_H__
