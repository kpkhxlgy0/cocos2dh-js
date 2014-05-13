/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   资源管理
 @History       (操作 -- 创建)(时间 -- 13-3-6)
 */

#include "HJSCocos2dxStudioPlus.h"
#include "../HJSHelper.h"
#include "cocos2d_specifics.hpp"

#include "jsb_cocos2dx_studio_plus_auto.hpp"

#include "cocostudio/CocoStudio.h"
#include "gui/CocosGui.h"

using namespace cocostudio;
using namespace gui;

#pragma mark - ComAttribute

JSBool js_cocos2dx_extension_plus_ComAttribute_getDict(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ComAttribute* cobj = (ComAttribute *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_extension_plus_ComAttribute_getDict : Invalid Native Object");
	if (argc == 0) {
        JsonDictionary *dict = cobj->getDict();
		jsval jsret = anonEvaluate(cx, obj, dict->getDescription().c_str());
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "js_cocos2dx_extension_plus_ComRender_getNode : wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}

#pragma mark - ActionNode

JSBool js_cocos2dx_extension_plus_ActionNode_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ActionNode* cobj = (ActionNode *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_extension_plus_ActionNode_initWithDictionary : Invalid Native Object");
	if (argc == 2) {
        JsonDictionary arg0;
		cocos2d::Object* arg1;
        std::string str;
        jsval_to_std_string(cx, argv[0], &str);
        arg0.initWithDescription(str.c_str());
		do {
			if (!argv[1].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::Object*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_extension_plus_ActionNode_initWithDictionary : Error processing arguments");
		cobj->initWithDictionary(&arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "js_cocos2dx_extension_plus_ActionNode_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}

#pragma mark - ActionObject

JSBool js_cocos2dx_extension_plus_ActionObject_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ActionObject* cobj = (ActionObject *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_extension_plus_ActionObject_initWithDictionary : Invalid Native Object");
	if (argc == 2) {
        JsonDictionary arg0;
		cocos2d::Object* arg1;
        std::string str;
        jsval_to_std_string(cx, argv[0], &str);
        arg0.initWithDescription(str.c_str());
		do {
			if (!argv[1].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::Object*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_extension_plus_ActionObject_initWithDictionary : Error processing arguments");
		cobj->initWithDictionary(&arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "js_cocos2dx_extension_plus_ActionObject_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}

#pragma mark - ActionManagerEx

JSBool js_cocos2dx_extension_plus_ActionManagerEx_initWithDictionary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ActionManagerEx* cobj = (ActionManagerEx *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_extension_plus_ActionManagerEx_initWithDictionary : Invalid Native Object");
	if (argc == 3) {
		const char* arg0;
        JsonDictionary arg1;
		cocos2d::Object* arg2;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string str;
        jsval_to_std_string(cx, argv[1], &str);
        arg1.initWithDescription(str.c_str());
		do {
			if (!argv[2].isObject()) { ok = JS_FALSE; break; }
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg2 = (cocos2d::Object*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg2, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_extension_plus_ActionManagerEx_initWithDictionary : Error processing arguments");
		cobj->initWithDictionary(arg0, &arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "js_cocos2dx_extension_plus_ActionManagerEx_initWithDictionary : wrong number of arguments: %d, was expecting %d", argc, 3);
	return JS_FALSE;
}

#pragma mark - ^WidgetPropertiesReader*$

#define WIDGET_PROPERTIES_READER_CREATE_WIDGET_FUNC(VERSION) \
JSBool js_cocos2dx_extension_plus_WidgetPropertiesReader##VERSION##_createWidget(JSContext *cx, uint32_t argc, jsval *vp) {\
    jsval *argv = JS_ARGV(cx, vp);\
    JSBool ok = JS_TRUE;\
    JSObject *obj = JS_THIS_OBJECT(cx, vp);\
    js_proxy_t *proxy = jsb_get_js_proxy(obj);\
    WidgetPropertiesReader##VERSION* cobj = (WidgetPropertiesReader##VERSION*)(proxy ? proxy->ptr : NULL);\
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_extension_plus_WidgetPropertiesReader"#VERSION"_createWidget : Invalid Native Object");\
    if (argc == 3) {\
        JsonDictionary arg0;\
        const char *arg1;\
        const char *arg2;\
        std::string str;\
        jsval_to_std_string(cx, argv[0], &str);\
        arg0.initWithDescription(str.c_str());\
        jsval_to_charptr(cx, argv[1], &arg1);\
        jsval_to_charptr(cx, argv[2], &arg2);\
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_extension_plus_WidgetPropertiesReader"#VERSION"_createWidget : Error processing arguments");\
        UIWidget* ret = cobj->createWidget(&arg0, arg1, arg2);\
        jsval jsret;\
        do {\
            if (ret) {\
                js_proxy_t *proxy = js_get_or_create_proxy<UIWidget>(cx, ret);\
                jsret = OBJECT_TO_JSVAL(proxy->obj);\
            } else {\
                jsret = JSVAL_NULL;\
            }\
        } while (0);\
        JS_SET_RVAL(cx, vp, jsret);\
        return JS_TRUE;\
    }\
    JS_ReportError(cx, "js_cocos2dx_extension_plus_WidgetPropertiesReader"#VERSION"_createWidget : wrong number of arguments: %d, was expecting %d", argc, 3);\
    return JS_FALSE;\
}

#define WIDGET_PROPERTIES_READER_WIDGET_FROM_JSON_DICTIONARY_FUNC(VERSION) \
JSBool js_cocos2dx_extension_plus_WidgetPropertiesReader##VERSION##_widgetFromJsonDictionary(JSContext *cx, uint32_t argc, jsval *vp) {\
    jsval *argv = JS_ARGV(cx, vp);\
    JSBool ok = JS_TRUE;\
    JSObject *obj = JS_THIS_OBJECT(cx, vp);\
    js_proxy_t *proxy = jsb_get_js_proxy(obj);\
    WidgetPropertiesReader##VERSION* cobj = (WidgetPropertiesReader##VERSION*)(proxy ? proxy->ptr : NULL);\
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_extension_plus_WidgetPropertiesReader"#VERSION"_widgetFromJsonDictionary : Invalid Native Object");\
    if (argc == 1) {\
        JsonDictionary arg0;\
        std::string str;\
        jsval_to_std_string(cx, argv[0], &str);\
        arg0.initWithDescription(str.c_str());\
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_extension_plus_WidgetPropertiesReader"#VERSION"_widgetFromJsonDictionary : Error processing arguments");\
        UIWidget* ret = cobj->widgetFromJsonDictionary(&arg0);\
        jsval jsret;\
        do {\
            if (ret) {\
                js_proxy_t *proxy = js_get_or_create_proxy<UIWidget>(cx, ret);\
                jsret = OBJECT_TO_JSVAL(proxy->obj);\
            } else {\
                jsret = JSVAL_NULL;\
            }\
        } while (0);\
        JS_SET_RVAL(cx, vp, jsret);\
        return JS_TRUE;\
    }\
    JS_ReportError(cx, "js_cocos2dx_extension_plus_WidgetPropertiesReader"#VERSION"_widgetFromJsonDictionary : wrong number of arguments: %d, was expecting %d", argc, 1);\
    return JS_FALSE;\
}

#define WIDGET_PROPERTIES_READER_SET_FUNC(VERSION, FUNC) \
JSBool js_cocos2dx_extension_plus_WidgetPropertiesReader##VERSION##_##FUNC(JSContext *cx, uint32_t argc, jsval *vp) {\
	jsval *argv = JS_ARGV(cx, vp);\
	JSBool ok = JS_TRUE;\
	JSObject *obj = JS_THIS_OBJECT(cx, vp);\
	js_proxy_t *proxy = jsb_get_js_proxy(obj);\
	WidgetPropertiesReader##VERSION *cobj = (WidgetPropertiesReader##VERSION*)(proxy ? proxy->ptr : NULL);\
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_extension_plus_WidgetPropertiesReader"#VERSION"_"#FUNC" : Invalid Native Object");\
	if (argc == 2) {\
		UIWidget* arg0;\
        JsonDictionary arg1;\
		do {\
			if (!argv[0].isObject()) { ok = JS_FALSE; break; }\
			js_proxy_t *proxy;\
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);\
			proxy = jsb_get_js_proxy(tmpObj);\
			arg0 = (UIWidget*)(proxy ? proxy->ptr : NULL);\
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");\
		} while (0);\
        std::string str;\
        jsval_to_std_string(cx, argv[1], &str);\
        arg1.initWithDescription(str.c_str());\
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_extension_plus_WidgetPropertiesReader"#VERSION"_"#FUNC" : Error processing arguments");\
		cobj->FUNC(arg0, &arg1);\
		JS_SET_RVAL(cx, vp, JSVAL_VOID);\
		return JS_TRUE;\
	}\
	JS_ReportError(cx, "js_cocos2dx_extension_plus_WidgetPropertiesReader"#VERSION"_"#FUNC" : wrong number of arguments: %d, was expecting %d", argc, 2);\
	return JS_FALSE;\
}

WIDGET_PROPERTIES_READER_CREATE_WIDGET_FUNC(0250);
WIDGET_PROPERTIES_READER_WIDGET_FROM_JSON_DICTIONARY_FUNC(0250);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForWidgetFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setColorPropsForWidgetFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForButtonFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForCheckBoxFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForImageViewFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForLabelFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForLabelAtlasFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForLabelBMFontFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForLoadingBarFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForSliderFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForTextFieldFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForLayoutFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0250, setPropsForScrollViewFromJsonDictionary);

WIDGET_PROPERTIES_READER_CREATE_WIDGET_FUNC(0300);
WIDGET_PROPERTIES_READER_WIDGET_FROM_JSON_DICTIONARY_FUNC(0300);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForWidgetFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setColorPropsForWidgetFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForButtonFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForCheckBoxFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForImageViewFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForLabelFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForLabelAtlasFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForLabelBMFontFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForLoadingBarFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForSliderFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForTextFieldFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForLayoutFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForPageViewFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForScrollViewFromJsonDictionary);
WIDGET_PROPERTIES_READER_SET_FUNC(0300, setPropsForListViewFromJsonDictionary);

#pragma mark - SceneReader

JSBool js_cocos2dx_extension_plus_SceneReader_createNodeWithSceneFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	SceneReader* cobj = (SceneReader *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "js_cocos2dx_extension_plus_SceneReader_createNodeWithSceneFile : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "js_cocos2dx_extension_plus_SceneReader_createNodeWithSceneFile : Error processing arguments");
		Node* ret = cobj->createNodeWithSceneFile(arg0);
        jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::Node>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "js_cocos2dx_extension_plus_SceneReader_createNodeWithSceneFile : wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

#pragma mark - register

void register_HJSCocos2dxStudioPlus(JSContext* cx, JSObject* global) {
    HJSHELPER_DEFINEFUNC_INIT("cc");
    
    JS_DefineFunction(cx, jsb_ComAttribute_prototype, "getDict", js_cocos2dx_extension_plus_ComAttribute_getDict, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_ActionNode_prototype, "initWithDictionary", js_cocos2dx_extension_plus_ActionNode_initWithDictionary, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_ActionObject_prototype, "initWithDictionary", js_cocos2dx_extension_plus_ActionObject_initWithDictionary, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_ActionManagerEx_prototype, "initWithDictionary", js_cocos2dx_extension_plus_ActionManagerEx_initWithDictionary, 3, JSPROP_READONLY | JSPROP_PERMANENT);
    
#define GUIREADER_DEFINE_CREATE_WIDGET_FUNC(VERSION) JS_DefineFunction(cx, jsb_WidgetPropertiesReader##VERSION##_prototype, "createWidget", js_cocos2dx_extension_plus_WidgetPropertiesReader##VERSION##_createWidget, 3, JSPROP_READONLY | JSPROP_PERMANENT);
#define GUIREADER_DEFINE_WIDGET_FROM_JSON_DICTIONARY_FUNC(VERSION) JS_DefineFunction(cx, jsb_WidgetPropertiesReader##VERSION##_prototype, "widgetFromJsonDictionary", js_cocos2dx_extension_plus_WidgetPropertiesReader##VERSION##_widgetFromJsonDictionary, 1, JSPROP_READONLY | JSPROP_PERMANENT);
#define GUIREADER_DEFINE_SET_FUNC(VERSION, FUNC) JS_DefineFunction(cx, jsb_WidgetPropertiesReader##VERSION##_prototype, #FUNC, js_cocos2dx_extension_plus_WidgetPropertiesReader##VERSION##_##FUNC, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    GUIREADER_DEFINE_CREATE_WIDGET_FUNC(0250);
    GUIREADER_DEFINE_WIDGET_FROM_JSON_DICTIONARY_FUNC(0250);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForWidgetFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setColorPropsForWidgetFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForButtonFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForCheckBoxFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForImageViewFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForLabelFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForLabelAtlasFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForLabelBMFontFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForLoadingBarFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForSliderFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForTextFieldFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForLayoutFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0250, setPropsForScrollViewFromJsonDictionary);
    
    GUIREADER_DEFINE_CREATE_WIDGET_FUNC(0300);
    GUIREADER_DEFINE_WIDGET_FROM_JSON_DICTIONARY_FUNC(0300);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForWidgetFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setColorPropsForWidgetFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForButtonFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForCheckBoxFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForImageViewFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForLabelFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForLabelAtlasFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForLabelBMFontFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForLoadingBarFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForSliderFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForTextFieldFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForLayoutFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForPageViewFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForScrollViewFromJsonDictionary);
    GUIREADER_DEFINE_SET_FUNC(0300, setPropsForListViewFromJsonDictionary);
    
    JS_DefineFunction(cx, jsb_SceneReader_prototype, "createNodeWithSceneFile", js_cocos2dx_extension_plus_SceneReader_createNodeWithSceneFile, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}
