/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   资源管理
 @History       (操作 -- 创建)(时间 -- 13-3-6)
 */

#include "HJSCocos2dxPlus.h"

#include "HJSHelper.h"
#include "../../helper/network/HAssetsManager.h"
#include "cocos2d_specifics.hpp"

#include "jsb_cocos2dx_auto.hpp"

USING_NS_CC;

#pragma mark - utility functions

extern bool jsval_to_string_vector(JSContext* cx, jsval v, std::vector<std::string>& ret);

#pragma mark - HJSTextureAsyncLoaderWrapper

class HJSTextureAsyncLoaderWrapper :
public JSCallbackWrapper {
public:
    HJSTextureAsyncLoaderWrapper() : _count(0), _needUnroot(false) {}
    
    ~HJSTextureAsyncLoaderWrapper() {
        if (_needUnroot) {
            JSObject *thisObj = JSVAL_TO_OBJECT(_jsThisObj);
            JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_RemoveObjectRoot(cx, &thisObj);
        }
    }
    
    void setJSCallbackThis(jsval _jsThisObj) {
        JSCallbackWrapper::setJSCallbackThis(_jsThisObj);
        
        JSObject *thisObj = JSVAL_TO_OBJECT(_jsThisObj);
        js_proxy *p = jsb_get_js_proxy(thisObj);
        if (!p)
        {
            JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_AddObjectRoot(cx, &thisObj);
            _needUnroot = true;
        }
    }
    
    void loadImage(const std::vector<std::string> &files) {
        auto texCache = Director::getInstance()->getTextureCache();
        auto fileUtils = FileUtils::getInstance();
        for (const auto &v : files) {
            auto path = fileUtils->fullPathForFilename(v);
            if (cocos2d::h::HAssetsManager::isDirectory(path)) {
                auto vec = cocos2d::h::HAssetsManager::readdir(path, true);
                _count += vec.size();
                for (const auto &v1 : vec) {
                    texCache->addImageAsync(v1.c_str(), CC_CALLBACK_1(HJSTextureAsyncLoaderWrapper::onImageLoaded, this));
                }
            } else {
                ++_count;
                texCache->addImageAsync(v.c_str(), CC_CALLBACK_1(HJSTextureAsyncLoaderWrapper::onImageLoaded, this));
            }
        }
    }
private:
    void onImageLoaded(Ref *texture) {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);
        do {
            bool hasAction;
            if (JS_HasProperty(cx, thisObj, "onImageLoaded", &hasAction) && hasAction) {
                JS::RootedValue temp_retval(cx);
                if(!JS_GetProperty(cx, thisObj, "onImageLoaded", &temp_retval)) {
                    break;
                }
                if(temp_retval == JSVAL_VOID) {
                    break;
                }
                jsval dataVal[1];
                dataVal[0] = getJSObject(cx, static_cast<Texture2D*>(texture));
                
                JS_AddValueRoot(cx, dataVal);
                
                JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                
                jsval retval;
                JS_CallFunctionName(cx, thisObj, "onImageLoaded", 1, dataVal, &retval);
                
                removeJSObject(cx, static_cast<Texture2D*>(texture));
                
                JS_RemoveValueRoot(cx, dataVal);
            }
        } while (0);
        --_count;
        if (_count == 0) {
            jsval retval = JSVAL_NULL;
            
            bool hasAction;
            JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
            if (JS_HasProperty(cx, obj, "onImageLoadedEnd", &hasAction) && hasAction) {
                JS::RootedValue temp_retval(cx);
                if(!JS_GetProperty(cx, obj, "onImageLoadedEnd", &temp_retval)) {
                    return;
                }
                if(temp_retval == JSVAL_VOID) {
                    return;
                }
                
                JSAutoCompartment ac(cx, obj);
                
                JS_CallFunctionName(cx, obj, "onImageLoadedEnd", 0, nullptr, &retval);
            }
            autorelease();
        }
    }
private:
    int _count;
    bool _needUnroot;
};

#pragma mark - cchGlobalFunction **************************

bool js_cocos2dxh_MessageBox(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
    
	if (argc == 2) {
        JSStringWrapper strMsg(JSVAL_TO_STRING(argv[0]));
        JSStringWrapper strTitle(JSVAL_TO_STRING(argv[1]));
        
        MessageBox(strMsg.get(), strTitle.get());
		
		return true;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_setEventEnabled(JSContext *cx, uint32_t argc, jsval *vp) {
    jsval *argv = JS_ARGV(cx, vp);
	if (argc == 1) {
        bool arg0 = (JSVAL_TO_BOOLEAN(argv[0]) == 1);
        Director::getInstance()->getEventDispatcher()->setEnabled(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_NULL);
		return true;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dxh_isEventEnabled(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
        bool ret = Director::getInstance()->getEventDispatcher()->isEnabled();
        jsval jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}

bool js_cocos2dxh_addImageAsync(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc >= 2) {
		jsval *argv = JS_ARGV(cx, vp);
        
        HJSTextureAsyncLoaderWrapper *tmpCobj = new HJSTextureAsyncLoaderWrapper();
        
        tmpCobj->setJSCallbackThis(argv[0]);
        
        std::string file;
        std::vector<std::string> files;
        std::vector<std::string> vec;
        for (uint32_t i = 1; i < argc; ++i) {
            JSObject *jsobj;
            jsobj = JSVAL_TO_OBJECT(argv[i]);
            if (jsobj && JS_IsArrayObject(cx, jsobj)) {
                jsval_to_string_vector(cx, argv[i], files);
                vec.insert(vec.end(), files.begin(), files.end());
            } else {
                jsval_to_std_string(cx, argv[i], &file);
                vec.push_back(file);
            }
        }
        tmpCobj->loadImage(vec);
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}

#pragma mark - EGLView

bool js_cocos2dx_EGLViewProtocol_getFrameSize(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::GLView* cobj = (cocos2d::GLView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_EGLViewProtocol_getFrameSize : Invalid Native Ref");
	if (argc == 0) {
		cocos2d::Size ret = cobj->getFrameSize();
		jsval jsret;
		jsret = ccsize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dx_EGLViewProtocol_getFrameSize : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

#pragma mark - register

void register_HJSCocos2dxPlus(JSContext* cx, JSObject* global) {
    HJSHELPER_DEFINEFUNC_INIT("cch");
    
    JS_DefineFunction(cx, global, "MessageBox", js_cocos2dxh_MessageBox, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "addImageAsync", js_cocos2dxh_addImageAsync, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "setEventEnabled", js_cocos2dxh_setEventEnabled, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "isEventEnabled", js_cocos2dxh_isEventEnabled, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_cocos2d_GLViewProtocol_prototype, "getFrameSize", js_cocos2dx_EGLViewProtocol_getFrameSize, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}
