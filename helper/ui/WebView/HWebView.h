#ifndef __HELPER_UI_WEBVIEW_HWEBVIEW__
#define __HELPER_UI_WEBVIEW_HWEBVIEW__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

class HWebView;
class HWebViewImpl;

enum HTUIWebViewNavigationType {
    HEUIWebViewNavigationTypeLinkClicked,
    HEUIWebViewNavigationTypeFormSubmitted,
    HEUIWebViewNavigationTypeBackForward,
    HEUIWebViewNavigationTypeReload,
    HEUIWebViewNavigationTypeFormResubmitted,
    HEUIWebViewNavigationTypeOther
};

class HWebViewDelegate {
public:
    virtual ~HWebViewDelegate() {}
    virtual bool webViewShouldStartLoadWithUrl(HWebView* INwebView, const char *INurl, HTUIWebViewNavigationType INtype) { return true;}
    virtual void webViewDidStartLoad(HWebView* INwebView) {}
    virtual void webViewDidFinishLoad(HWebView* INwebView) {}
    virtual void didFailLoad(HWebView* INwebView) {}
};

class HWebView : public Node {
public:
    HWebView();
	~HWebView();
	bool initWithSize(const Size& INsize);
    
	virtual void setPosition(const Point& pos);
    virtual void setVisible(bool visible);
    virtual void setContentSize(const Size& size);
	virtual void setAnchorPoint(const Point& anchorPoint);
    virtual void visit(Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated) override;
	virtual void onEnter(void);
    virtual void onExit(void);
	
	void setDelegate(HWebViewDelegate* INpDelegate);
	
	void loadURL(const char* INurl);
    
    void stopLoading();
	void reload();
    
	void goBack();
	void goForward();
    
	bool canGoBack();
	bool canGoForward();
    bool isLoading();
public:
	static HWebView* create(const Size& INsize);
private:
	HWebViewImpl*		m_pWebViewImpl;
};

NS_CC_H_END

#endif // __HELPER_UI_WEBVIEW_HWEBVIEW__

