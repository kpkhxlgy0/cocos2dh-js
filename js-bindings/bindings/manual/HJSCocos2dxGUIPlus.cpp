/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   资源管理
 @History       (操作 -- 创建)(时间 -- 13-3-6)
 */

#include "HJSCocos2dxGUIPlus.h"
#include "../HJSHelper.h"
#include "cocos2d_specifics.hpp"

#include "jsb_cocos2dx_gui_plus_auto.hpp"

#include "cocostudio/CocoStudio.h"
#include "gui/CocosGui.h"

using namespace cocostudio;
using namespace gui;

#pragma mark - utility functions

// setBlendFunc
template<class T>
JSBool js_cocos2dx_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj;
    T* cobj;
    obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (T*)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)
    if (argc == 2)
    {
        GLenum src, dst;
        jsval_to_int32(cx, argv[0], (int32_t*)&src);
        jsval_to_int32(cx, argv[1], (int32_t*)&dst);
        BlendFunc blendFunc = {src, dst};
        cobj->setBlendFunc(blendFunc);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
    return JS_FALSE;
}

extern JSBool jsval_to_UIMargin(JSContext *cx, jsval v, UIMargin* ret);
extern jsval UIMargin_to_jsval(JSContext* cx, const UIMargin& v);

#pragma mark - HJSUIWidgetTouchEventWrapper

#define UIWIDGET_ONEVENT(event, eventType) void on##event##Event(Object *sender, eventType type) {\
    processEvent(sender, type);\
}
class HJSUIWidgetEventWrapper :
public JSCallbackWrapper {
public:
    UIWIDGET_ONEVENT(Touch, TouchEventType);
    
    UIWIDGET_ONEVENT(PageView, PageViewEventType);
    UIWIDGET_ONEVENT(ScrollView, ScrollviewEventType);
    
    UIWIDGET_ONEVENT(CheckBox, CheckBoxEventType);
    UIWIDGET_ONEVENT(Slider, SliderEventType);
    UIWIDGET_ONEVENT(TextField, TextFiledEventType);
private:
    void processEvent(Object *sender, int type) {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        js_proxy_t *p;
        JS_GET_PROXY(p, sender);
        if (!p) {
            log("Failed to get proxy");
            return;
        }
        
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        dataVal[1] = INT_TO_JSVAL(type);
        
        if(!JSVAL_IS_VOID(_jsCallback)  && !JSVAL_IS_VOID(_jsThisObj)) {
            JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(_jsThisObj), _jsCallback, 2, dataVal, &retval);
        }
    }
};

#pragma mark - UIWidget

#define UIWIDGET_EVENT_FUNC(type, func, sel, event) static JSBool js_cocos2dx_extension_plus_##type##_##func(JSContext *cx, uint32_t argc, jsval *vp) {\
    if (argc == 2) {\
        jsval *argv = JS_ARGV(cx, vp);\
        JSB_PRECONDITION2(argv[0] != JSVAL_NULL && argv[1] != JSVAL_NULL, cx, JS_FALSE, "arg0 and arg1 must not be null");\
        JSObject *obj = JS_THIS_OBJECT(cx, vp);\
        js_proxy_t *proxy;\
        JS_GET_NATIVE_PROXY(proxy, obj);\
        auto node = (type*)(proxy ? proxy->ptr : NULL);\
        auto tmpCobj = new HJSUIWidgetEventWrapper();\
        tmpCobj->autorelease();\
        auto dict = static_cast<Dictionary*>(node->getUserObject());\
        if (!dict) {\
            dict = Dictionary::create();\
            node->setUserObject(dict);\
        }\
        dict->setObject(tmpCobj, "event"#event);\
        node->func(tmpCobj, sel(HJSUIWidgetEventWrapper::on##event##Event));\
        tmpCobj->setJSCallbackThis(argv[0]);\
        tmpCobj->setJSCallbackFunc(argv[1]);\
        return JS_TRUE;\
    }\
    JS_ReportError(cx, "wrong number of arguments");\
    return JS_FALSE;\
}
JSBool js_cocos2dx_extension_plus_UIWidget_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    return js_cocos2dx_setBlendFunc<UIWidget>(cx, argc, vp);
}
UIWIDGET_EVENT_FUNC(UIWidget, addTouchEventListener, toucheventselector, Touch);

UIWIDGET_EVENT_FUNC(UIPageView, addEventListenerPageView, pagevieweventselector, PageView);
UIWIDGET_EVENT_FUNC(UIScrollView, addEventListenerScrollView, scrollvieweventselector, ScrollView);

UIWIDGET_EVENT_FUNC(UICheckBox, addEventListenerCheckBox, checkboxselectedeventselector, CheckBox);
UIWIDGET_EVENT_FUNC(UISlider, addEventListenerSlider, sliderpercentchangedselector, Slider);
UIWIDGET_EVENT_FUNC(UITextField, addEventListenerTextField, textfieldeventselector, TextField);

#pragma mark - LayoutParameter

JSBool js_cocos2dx_extension_plus_LayoutParameter_setMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	UILayoutParameter* cobj = (UILayoutParameter *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_extension_plus_LayoutParameter_setMargin : Invalid Native Object");
	if (argc == 1) {
		UIMargin arg0;
		jsval_to_UIMargin(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_extension_plus_LayoutParameter_setMargin : Error processing arguments");
		cobj->setMargin(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "js_cocos2dx_extension_plus_LayoutParameter_setMargin : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_extension_plus_LayoutParameter_getMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	UILayoutParameter* cobj = (UILayoutParameter *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_extension_plus_LayoutParameter_getMargin : Invalid Native Object");
	if (argc == 0) {
		UIMargin ret = cobj->getMargin();
		jsval jsret = UIMargin_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "js_cocos2dx_extension_plus_LayoutParameter_getMargin : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}

#pragma mark - register

void register_HJSCocos2dxGUIPlus(JSContext* cx, JSObject* global) {
    HJSHELPER_DEFINEFUNC_INIT("cc");
    
    JS_DefineFunction(cx, jsb_UIWidget_prototype, "setBlendFunc", js_cocos2dx_extension_plus_UIWidget_setBlendFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);
#define UIWIDEGT_DEFINE_FUNC(type, func) JS_DefineFunction(cx, jsb_##type##_prototype, #func, js_cocos2dx_extension_plus_##type##_##func, 2, JSPROP_READONLY | JSPROP_PERMANENT)
    
    UIWIDEGT_DEFINE_FUNC(UIWidget, addTouchEventListener);
    
    UIWIDEGT_DEFINE_FUNC(UIPageView, addEventListenerPageView);
    UIWIDEGT_DEFINE_FUNC(UIScrollView, addEventListenerScrollView);
    
    UIWIDEGT_DEFINE_FUNC(UICheckBox, addEventListenerCheckBox);
    UIWIDEGT_DEFINE_FUNC(UISlider, addEventListenerSlider);
    UIWIDEGT_DEFINE_FUNC(UITextField, addEventListenerTextField);
    
    JS_DefineFunction(cx, jsb_UILayoutParameter_prototype, "setMargin", js_cocos2dx_extension_plus_LayoutParameter_setMargin, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_UILayoutParameter_prototype, "getMargin", js_cocos2dx_extension_plus_LayoutParameter_getMargin, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}
