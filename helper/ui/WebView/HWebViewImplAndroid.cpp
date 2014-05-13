#include "HWebViewImplAndroid.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "../../../cocos2dx/platform/android/jni/JniHelper.h"
#include <jni.h>

#define  CLASS_NAME "org/cocos2dxh/lib/Cocos2dxhWebView"

NS_CC_H_BEGIN

extern "C" {
    // static void createWebViewWithSizeJNI(float INw, float INh, void *INobj) {
    //     JNIEnv *env = NULL;
    //     jclass cls = JniHelper::getClassID(CLASS_NAME, env);
    //     env->NewObject();
    //     JniMethodInfo t;
    //     std::string ret("");

    //     if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "generateUuid", "()Ljava/lang/String;")) {
    //         jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
    //         t.env->DeleteLocalRef(t.classID);
    //         ret = JniHelper::jstring2string(str);
    //         t.env->DeleteLocalRef(str);
    //     }
    //     memcpy(INuuid, ret.c_str(), ret.length());
    // }
    static void loadURLJNI(const char *INurl) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, "org/cocos2dxh/lib/Cocos2dxhHelper", "loadURL", "(Ljava/lang/String;)V")) {
            jstring strArg0 = t.env->NewStringUTF(INurl);
            t.env->CallStaticObjectMethod(t.classID, t.methodID, strArg0);
            t.env->DeleteLocalRef(strArg0);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}

HWebViewImpl* createSystemWebView(HWebView* INwebView) {
    return new HWebViewImplAndroid(INwebView);
}

HWebViewImplAndroid::HWebViewImplAndroid(HWebView* INwebView) : HWebViewImpl(INwebView),
m_systemControl(NULL) {
}

HWebViewImplAndroid::~HWebViewImplAndroid() {
    free(m_systemControl);
}

bool HWebViewImplAndroid::initWithSize(const cocos2d::CCSize &INsize) {
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

void HWebViewImplAndroid::setPosition(const cocos2d::CCPoint &INpoint) {
//  [m_pSystemControl setPosition:convertDesignCoordToScreenCoord(ccp(INpoint.x - m_cContentSize.width / 2, INpoint.y + m_cContentSize.height / 2), m_bInRetinaMode)];
}
void HWebViewImplAndroid::setVisible(bool visible) {
    // [m_systemControl setVisible:visible];
}
void HWebViewImplAndroid::setContentSize(const cocos2d::CCSize &INsize) {
//  m_cContentSize = INsize;
////    CCLOG("[Edit text] content size = (%f, %f)", INsize.width, INsize.height);
}
void HWebViewImplAndroid::setAnchorPoint(const CCPoint& anchorPoint) {
    // CCLOG("[WebView] anchor point = (%f, %f)", anchorPoint.x, anchorPoint.y);
    // m_obAnchorPoint = anchorPoint;
    // setPosition(m_obPosition);
}
void HWebViewImplAndroid::visit(void) {
    
}
void HWebViewImplAndroid::onEnter(void) {
    // [m_systemControl onEnter];
    // adjustTextFieldPosition();
}
void HWebViewImplAndroid::onExit(void) {
    // [m_systemControl onExit];
}

void HWebViewImplAndroid::loadURL(const char *INurl) {
//  [m_pSystemControl loadURL:INurl];
    loadURLJNI(INurl);
}

void HWebViewImplAndroid::stopLoading() {
    // [m_systemControl stopLoading];
}
void HWebViewImplAndroid::reload() {
    // [m_systemControl reload];
}

void HWebViewImplAndroid::goBack() {
//  [m_pSystemControl goBack];
}
void HWebViewImplAndroid::goForward() {
//  [m_pSystemControl goForward];
}

bool HWebViewImplAndroid::canGoBack() {
//  return [m_pSystemControl canGoBack] ? true : false;
    return true;
}
bool HWebViewImplAndroid::canGoForward() {
//  return [m_pSystemControl canGoForward] ? true : false;
    return true;
}
bool HWebViewImplAndroid::isLoading() {
    // return [m_systemControl isLoading];
    return false;
}

void HWebViewImplAndroid::adjustTextFieldPosition() {
    CCSize contentSize = m_pWebView->getContentSize();
    CCRect rect = CCRectMake(0, 0, contentSize.width, contentSize.height);
    rect = CCRectApplyAffineTransform(rect, m_pWebView->nodeToWorldTransform());
    
    CCPoint designCoord = ccp(rect.origin.x, rect.origin.y);
    // [m_systemControl setPosition:convertDesignCoordToScreenCoord(designCoord)];
}

NS_CC_H_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */
