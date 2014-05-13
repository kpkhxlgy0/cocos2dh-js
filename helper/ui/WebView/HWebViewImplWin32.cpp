#include "HWebViewImplWin32.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

NS_CC_H_BEGIN

HWebViewImpl* createSystemWebView(HWebView* INwebView) {
    return new HWebViewImplWin32(INwebView);
}

HWebViewImplWin32::HWebViewImplWin32(HWebView* INwebView) : HWebViewImpl(INwebView),
m_systemControl(NULL) {
}

HWebViewImplWin32::~HWebViewImplWin32() {
    free(m_systemControl);
}

bool HWebViewImplWin32::initWithSize(const cocos2d::CCSize &INsize) {
    do {
//        CCEGLViewProtocol* pEGLView = CCEGLView::sharedOpenGLView();
//
//        CGRect rect = CGRectMake(0, 0, INsize.width * pEGLView->getScaleX(), INsize.height * pEGLView->getScaleY());
//
//        if (m_bInRetinaMode)
//        {
//            rect.size.width *= 0.5f;
//            rect.size.height *= 0.5f;
//        }
//      
//      m_pSystemControl = [[HUIWebView alloc] initWithFrame:rect andWebView:this];
//      CC_BREAK_IF(!m_pSystemControl);
        
        return true;
    }while (0);
    return false;
}

static CCPoint convertDesignCoordToScreenCoord(const CCPoint& designCoord) {
    CCEGLViewProtocol* eglView = CCEGLView::sharedOpenGLView();
    
    CCPoint visiblePos = ccp(designCoord.x * eglView->getScaleX(), designCoord.y * eglView->getScaleY());
    CCPoint screenGLPos = ccpAdd(visiblePos, eglView->getViewPortRect().origin);
    
    CCPoint screenPos = screenGLPos;
    
    CCLOG("[WebView] pos x = %f, y = %f", screenGLPos.x, screenGLPos.y);
    return screenPos;
}

void HWebViewImplWin32::setPosition(const cocos2d::CCPoint &INpoint) {
//  [m_pSystemControl setPosition:convertDesignCoordToScreenCoord(ccp(INpoint.x - m_cContentSize.width / 2, INpoint.y + m_cContentSize.height / 2), m_bInRetinaMode)];
}
void HWebViewImplWin32::setVisible(bool visible) {
    // [m_systemControl setVisible:visible];
}
void HWebViewImplWin32::setContentSize(const cocos2d::CCSize &INsize) {
//  m_cContentSize = INsize;
////    CCLOG("[Edit text] content size = (%f, %f)", INsize.width, INsize.height);
}
void HWebViewImplWin32::setAnchorPoint(const CCPoint& anchorPoint) {
    // CCLOG("[WebView] anchor point = (%f, %f)", anchorPoint.x, anchorPoint.y);
    // m_obAnchorPoint = anchorPoint;
    // setPosition(m_obPosition);
}
void HWebViewImplWin32::visit(void) {
    
}
void HWebViewImplWin32::onEnter(void) {
    // [m_systemControl onEnter];
    // adjustTextFieldPosition();
}
void HWebViewImplWin32::onExit(void) {
    // [m_systemControl onExit];
}

void HWebViewImplWin32::loadURL(const char *INurl) {
//  [m_pSystemControl loadURL:INurl];
//  loadURLJNI(INurl);
}

void HWebViewImplWin32::stopLoading() {
    // [m_systemControl stopLoading];
}
void HWebViewImplWin32::reload() {
    // [m_systemControl reload];
}

void HWebViewImplWin32::goBack() {
//  [m_pSystemControl goBack];
}
void HWebViewImplWin32::goForward() {
//  [m_pSystemControl goForward];
}

bool HWebViewImplWin32::canGoBack() {
//  return [m_pSystemControl canGoBack] ? true : false;
    return true;
}
bool HWebViewImplWin32::canGoForward() {
//  return [m_pSystemControl canGoForward] ? true : false;
    return true;
}
bool HWebViewImplWin32::isLoading() {
    // return [m_systemControl isLoading];
    return false;
}

void HWebViewImplWin32::adjustTextFieldPosition() {
//     CCSize contentSize = m_pWebView->getContentSize();
//     CCRect rect = CCRectMake(0, 0, contentSize.width, contentSize.height);
//     rect = CCRectApplyAffineTransform(rect, m_pWebView->nodeToWorldTransform());
//     
//     CCPoint designCoord = ccp(rect.origin.x, rect.origin.y);
    // [m_systemControl setPosition:convertDesignCoordToScreenCoord(designCoord)];
}

NS_CC_H_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */
