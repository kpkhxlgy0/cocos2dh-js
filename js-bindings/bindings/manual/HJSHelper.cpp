/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   资源管理
 @History       (操作 -- 创建)(时间 -- 13-3-6)
 */

#include "HJSHelper.h"

#include "ScriptingCore.h"

#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

namespace js {
extern JS_PUBLIC_API(bool)
    IsInRequest(JSContext *cx) {
        return true;
    }
}

#pragma mark - utility functions

bool jsval_to_int8(JSContext *cx, jsval vp, int8_t *ret) {
    int32_t temp = JSVAL_TO_INT(vp);
    *ret = (int8_t)temp;
    return true;
}
bool jsval_to_uint8(JSContext *cx, jsval vp, uint8_t *ret) {
    bool ok = true;
    double dp;
    dp = JSVAL_TO_DOUBLE(vp);
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
    *ret = (uint8_t)dp;
    return ok;
}
bool jsval_to_int16(JSContext *cx, jsval vp, int16_t *ret) {
    int32_t temp = JSVAL_TO_INT(vp);
    *ret = (int16_t)temp;
    return true;
}
bool jsval_to_int64(JSContext *cx, jsval vp, int64_t *ret) {
    bool ok = true;
    double dp;
    dp = JSVAL_TO_DOUBLE(vp);
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
    *ret = (int64_t)dp;
    return ok;
}
bool jsval_to_uint64(JSContext *cx, jsval vp, uint64_t *ret) {
    bool ok = true;
    double dp;
    dp = JSVAL_TO_DOUBLE(vp);
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
    *ret = (uint64_t)dp;
    return ok;
}
bool jsval_to_string_vector(JSContext* cx, jsval v, std::vector<std::string>& ret) {
    JSObject *jsobj;
    jsobj = JSVAL_TO_OBJECT(v);
	JSB_PRECONDITION2( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    
    for (uint32_t i=0; i < len; i++) {
        JS::RootedValue elt(cx);
        if (JS_GetElement(cx, jsobj, i, &elt)) {
            
            if (JSVAL_IS_STRING(elt))
            {
                JSStringWrapper str(JSVAL_TO_STRING(elt));
                ret.push_back(str.get());
            }
        }
    }
    return true;
}
bool jsval_to_UIMargin(JSContext *cx, jsval v, Margin* ret) {
    JSObject *tmp;
    JS::RootedValue jsl(cx), jst(cx), jsr(cx), jsb(cx);
    double l, t, r, b;
    bool ok = v.isObject();
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    tmp = JSVAL_TO_OBJECT(v);
    ok = JS_GetProperty(cx, tmp, "l", &jsl) &&
    JS_GetProperty(cx, tmp, "t", &jst) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "b", &jsb);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    l = JSVAL_TO_DOUBLE(jsl);
    t = JSVAL_TO_DOUBLE(jst);
    r = JSVAL_TO_DOUBLE(jsr);
    b = JSVAL_TO_DOUBLE(jsb);
    
    ret->setMargin(l, t, r, b);
    return true;
}

jsval int8_to_jsval(JSContext* cx, int8_t v) {
    return INT_TO_JSVAL(v);
}
jsval uint8_to_jsval(JSContext* cx, uint8_t v) {
    return UINT_TO_JSVAL(v);
}
jsval int16_to_jsval(JSContext* cx, int16_t v) {
    return INT_TO_JSVAL(v);
}
jsval uint16_to_jsval(JSContext* cx, uint16_t v) {
    return UINT_TO_JSVAL(v);
}
jsval int64_to_jsval(JSContext* cx, int64_t v) {
    return DOUBLE_TO_JSVAL(v);
}
jsval uint64_to_jsval(JSContext* cx, uint64_t v) {
    return DOUBLE_TO_JSVAL(v);
}
jsval string_vector_to_jsval(JSContext* cx, const std::vector<std::string>& arr) {
    
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0, NULL));
    
    int i = 0;
    for(std::vector<std::string>::const_iterator iter = arr.begin(); iter != arr.end(); ++iter, ++i) {
        JS::RootedValue arrElement(cx, c_string_to_jsval(cx, iter->c_str()));
        if(!JS_SetElement(cx, jsretArr, i, &arrElement)) {
            break;
        }
    }
    return OBJECT_TO_JSVAL(jsretArr);
}
jsval UIMargin_to_jsval(JSContext* cx, const Margin& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "l", DOUBLE_TO_JSVAL(v.left), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "t", DOUBLE_TO_JSVAL(v.top), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "r", DOUBLE_TO_JSVAL(v.right), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", DOUBLE_TO_JSVAL(v.bottom), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}
#define CASE_SETELEMENT(TYPE, ARRAYTYPE) TYPE##_t *v = (TYPE##_t*)data; \
JSObject *jsobj = JS_New##ARRAYTYPE##Array(cx, count); \
for (int i = 0; i < count; ++i) { \
JS::RootedValue arrElement(cx, TYPE##_to_jsval(cx, *(v + i))); \
JS_SetElement(cx, jsobj, i, &arrElement); \
} \
*vp = OBJECT_TO_JSVAL(jsobj); \
break;
bool JSB_dataptr_to_jsval_typedarray(JSContext *cx, jsval *vp, GLsizei count, void *data, JSArrayBufferViewType t) {
    switch (t) {
        case js::ArrayBufferView::TYPE_INT8: {
            CASE_SETELEMENT(int8, Int8);
        }
        case js::ArrayBufferView::TYPE_UINT8: {
            CASE_SETELEMENT(uint8, Uint8);
        }
        case js::ArrayBufferView::TYPE_INT16: {
            CASE_SETELEMENT(int16, Int16);
        }
        case js::ArrayBufferView::TYPE_UINT16: {
            CASE_SETELEMENT(uint16, Uint16);
        }
        case js::ArrayBufferView::TYPE_INT32: {
            CASE_SETELEMENT(int32, Int32);
        }
        case js::ArrayBufferView::TYPE_UINT32: {
            CASE_SETELEMENT(uint32, Uint32);
        }
        case js::ArrayBufferView::TYPE_FLOAT32: {
            float *v = (float*)data;
            JSObject *jsobj = JS_NewFloat32Array(cx, count);
            for (int i = 0; i < count; ++i) {
                JS::RootedValue arrElement(cx, DOUBLE_TO_JSVAL(*(v + i)));
                JS_SetElement(cx, jsobj, i, &arrElement);
            }
            *vp = OBJECT_TO_JSVAL(jsobj);
            break;
        }
        case js::ArrayBufferView::TYPE_FLOAT64: {
            double *v = (double*)data;
            JSObject *jsobj = JS_NewFloat64Array(cx, count);
            for (int i = 0; i < count; ++i) {
                JS::RootedValue arrElement(cx, DOUBLE_TO_JSVAL(*(v + i)));
                JS_SetElement(cx, jsobj, i, &arrElement);
            }
            *vp = OBJECT_TO_JSVAL(jsobj);
            break;
        }
        default:
            JSB_PRECONDITION2(false, cx, false, "Error new uint array");
            return false;
    }
	return true;
}

bool js_cocos2dxh_autorelease(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *thisObj = JS_THIS_OBJECT(cx, vp);
	if (thisObj) {
		js_proxy_t *proxy = jsb_get_js_proxy(thisObj);
		if (proxy) {
			((cocos2d::Ref *)proxy->ptr)->autorelease();
			return true;
		}
	}
    JS_ReportError(cx, "Invalid Native Object.");
	return false;
}

#pragma mark - HJSHelper

class HJSHelper : public cocos2d::Ref {
public:
    HJSHelper() {}
    ~HJSHelper() {}
    bool init() {return true;}
    
    void restartScript(const char *INscriptFile) {
        m_script = INscriptFile;
        auto scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->unschedule(schedule_selector(HJSHelper::tickRestartScript), this);
        scheduler->schedule(schedule_selector(HJSHelper::tickRestartScript), this, 0, false);
    }
public:
    static HJSHelper* getInstance() {
        if (!s_sharedHJSHelper) {
            s_sharedHJSHelper = new HJSHelper();
            s_sharedHJSHelper->init();
        }
        return s_sharedHJSHelper;
    }
    static void destroyInstance() {
        if (s_sharedHJSHelper) {
            cocos2d::Director::getInstance()->getScheduler()->unschedule(schedule_selector(HJSHelper::tickRestartScript), s_sharedHJSHelper);
        }
        delete s_sharedHJSHelper;
        s_sharedHJSHelper = NULL;
    }
private:
    void tickRestartScript(float INdt) {
        auto sc = ScriptingCore::getInstance();
        auto director = cocos2d::Director::getInstance();
        sc->reset();
        director->getScheduler()->unschedule(schedule_selector(HJSHelper::tickRestartScript), s_sharedHJSHelper);
        director->purgeCachedData();
        sc->runScript(m_script.c_str());
    }
private:
    static HJSHelper *s_sharedHJSHelper;
    std::string m_script;
};
HJSHelper *HJSHelper::s_sharedHJSHelper = nullptr;

bool js_cocos2dxh_restartScript(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
    
	if (argc == 1) {
        JSStringWrapper strScriptFile(JSVAL_TO_STRING(argv[0]));
        
        HJSHelper::getInstance()->restartScript(strScriptFile.get());
		
		return true;
	}
	
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

#pragma mark - register

void register_HJSHelper(JSContext* cx, JSObject* global) {
    HJSHELPER_DEFINEFUNC_INIT("cch");
    
    JS_DefineFunction(cx, global, "restartScript", js_cocos2dxh_restartScript, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}
