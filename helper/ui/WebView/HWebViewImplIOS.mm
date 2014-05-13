#include "HWebViewImplIOS.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#import "CCEAGLView.h"

#define getWebViewImplIOS() ((cocos2d::h::HWebViewImplIOS*)m_pWebViewImpl)

@implementation HUIWebView

@synthesize m_pWebViewImpl;

- (void)dealloc {
    [m_pUIWebView removeFromSuperview];
    [m_pUIWebView release];
    [super dealloc];
}

- (id)initWithFrame:(CGRect)INframeRect andWebView:(void *)INwebView {
    if (self = [super init]) {
        m_pUIWebView = [[UIWebView alloc] initWithFrame:INframeRect];
        m_pUIWebView.scalesPageToFit = YES;
        m_pUIWebView.delegate = self;
        
        m_pWebViewImpl = INwebView;
    }
    return self;
}
- (void)setPosition:(CGPoint)INpoint {
    CGRect frame = [m_pUIWebView frame];
    frame.origin = INpoint;
    m_pUIWebView.frame = frame;
}
- (void)setVisible:(BOOL)INvisible {
    m_pUIWebView.hidden = !INvisible;
}
- (void)setContentSize:(CGSize)INsize {
    CGRect frame = [m_pUIWebView frame];
    frame.size = INsize;
    [m_pUIWebView setFrame:frame];
}
- (void)onEnter {
    [(CCEAGLView*)cocos2d::Director::getInstance()->getOpenGLView()->getEAGLView() addSubview:m_pUIWebView];
}
- (void)onExit {
    [m_pUIWebView removeFromSuperview];
}

- (void)loadURL:(const char *)INurl {
    [m_pUIWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:INurl]]]];
}

- (void)stopLoading {
    [m_pUIWebView stopLoading];
}
- (void)reload {
    [m_pUIWebView reload];
}

- (void)goBack {
    [m_pUIWebView goBack];
}
- (void)goForward {
    [m_pUIWebView goForward];
}

- (BOOL)canGoBack {
    return [m_pUIWebView canGoBack];
}
- (BOOL)canGoForward {
    return [m_pUIWebView canGoForward];
}
- (BOOL)isLoading {
    return [m_pUIWebView isLoading];
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType {
    if (getWebViewImplIOS()->getDelegate()) {
        return getWebViewImplIOS()->getDelegate()->webViewShouldStartLoadWithUrl(getWebViewImplIOS()->getWebView(), [request.URL.absoluteString UTF8String], (cocos2d::h::HTUIWebViewNavigationType)navigationType);
    }
    return YES;
}

- (void)webViewDidStartLoad:(UIWebView *)webView {
    if (getWebViewImplIOS()->getDelegate()) {
        getWebViewImplIOS()->getDelegate()->webViewDidStartLoad(getWebViewImplIOS()->getWebView());
    }
}

- (void)webViewDidFinishLoad:(UIWebView *)webView {
    if (getWebViewImplIOS()->getDelegate()) {
        getWebViewImplIOS()->getDelegate()->webViewDidFinishLoad(getWebViewImplIOS()->getWebView());
    }
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error {
    if (getWebViewImplIOS()->getDelegate()) {
        getWebViewImplIOS()->getDelegate()->didFailLoad(getWebViewImplIOS()->getWebView());
    }
}

@end

NS_CC_H_BEGIN

HWebViewImpl* createSystemWebView(HWebView* INwebView) {
    return new HWebViewImplIOS(INwebView);
}

HWebViewImplIOS::HWebViewImplIOS(HWebView* INwebView) : HWebViewImpl(INwebView) {
    m_bInRetinaMode = [(CCEAGLView*)Director::getInstance()->getOpenGLView()->getEAGLView() contentScaleFactor] == 2.0f ? true : false;
}

HWebViewImplIOS::~HWebViewImplIOS() {
    [m_systemControl release];
}

bool HWebViewImplIOS::initWithSize(const Size &INsize) {
    do {
        GLView* eglView = Director::getInstance()->getOpenGLView();
        
        CGRect rect = CGRectMake(0, 0, INsize.width * eglView->getScaleX(), INsize.height * eglView->getScaleY());
        
        if (m_bInRetinaMode) {
            rect.size.width /= 2.0f;
            rect.size.height /= 2.0f;
        }
        
        m_systemControl = [[HUIWebView alloc] initWithFrame:rect andWebView:this];
        if (!m_systemControl) break;
        
        setContentSize(INsize);
        
        return true;
    }while (0);
    return false;
}

static CGPoint convertDesignCoordToScreenCoord(const Point& designCoord, bool bInRetinaMode) {
    GLView* eglView = Director::getInstance()->getOpenGLView();
    float viewH = (float)[(CCEAGLView*)Director::getInstance()->getOpenGLView()->getEAGLView() getHeight];
    
    Point visiblePos = Point(designCoord.x * eglView->getScaleX(), designCoord.y * eglView->getScaleY());
    Point screenGLPos = visiblePos + eglView->getViewPortRect().origin;
    
    CGPoint screenPos = CGPointMake(screenGLPos.x, viewH - screenGLPos.y);
    
    if (bInRetinaMode)
    {
        screenPos.x = screenPos.x / 2.0f;
        screenPos.y = screenPos.y / 2.0f;
    }
    CCLOG("[WebView] pos x = %f, y = %f", screenGLPos.x, screenGLPos.y);
    return screenPos;
}

void HWebViewImplIOS::setPosition(const Point &INpoint) {
    m_obPosition = INpoint;
    adjustTextFieldPosition();
}
void HWebViewImplIOS::setVisible(bool visible) {
    [m_systemControl setVisible:visible];
}
void HWebViewImplIOS::setContentSize(const Size &INsize) {
    m_tContentSize = INsize;
    CCLOG("[WebView] content size = (%f, %f)", INsize.width, INsize.height);
    GLView* eglView = Director::getInstance()->getOpenGLView();
    CGSize controlSize = CGSizeMake(INsize.width * eglView->getScaleX(),INsize.height * eglView->getScaleY());
    
    if (m_bInRetinaMode)
    {
        controlSize.width /= 2.0f;
        controlSize.height /= 2.0f;
    }
    [m_systemControl setContentSize:controlSize];
    
    adjustTextFieldPosition();
}
void HWebViewImplIOS::setAnchorPoint(const Point& anchorPoint) {
    CCLOG("[WebView] anchor point = (%f, %f)", anchorPoint.x, anchorPoint.y);
    m_obAnchorPoint = anchorPoint;
    setPosition(m_obPosition);
}
void HWebViewImplIOS::visit(void) {
    
}
void HWebViewImplIOS::onEnter(void) {
    [m_systemControl onEnter];
    adjustTextFieldPosition();
}
void HWebViewImplIOS::onExit(void) {
    [m_systemControl onExit];
}

void HWebViewImplIOS::loadURL(const char *INurl) {
    [m_systemControl loadURL:INurl];
}

void HWebViewImplIOS::stopLoading() {
    [m_systemControl stopLoading];
}
void HWebViewImplIOS::reload() {
    [m_systemControl reload];
}

void HWebViewImplIOS::goBack() {
    [m_systemControl goBack];
}
void HWebViewImplIOS::goForward() {
    [m_systemControl goForward];
}

bool HWebViewImplIOS::canGoBack() {
    return [m_systemControl canGoBack];
}
bool HWebViewImplIOS::canGoForward() {
    return [m_systemControl canGoForward];
}
bool HWebViewImplIOS::isLoading() {
    return [m_systemControl isLoading];
}

void HWebViewImplIOS::adjustTextFieldPosition() {
    Size contentSize = m_pWebView->getContentSize();
    Rect rect = Rect(0, 0, contentSize.width, contentSize.height);
    rect = RectApplyAffineTransform(rect, m_pWebView->nodeToWorldTransform());
    
    Point designCoord(rect.origin.x, rect.origin.y + rect.size.height);
    [m_systemControl setPosition:convertDesignCoordToScreenCoord(designCoord, m_bInRetinaMode)];
}

NS_CC_H_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */


