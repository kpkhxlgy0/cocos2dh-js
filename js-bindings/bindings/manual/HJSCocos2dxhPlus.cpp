/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   资源管理
 @History       (操作 -- 创建)(时间 -- 13-3-6)
 */

#include "HJSCocos2dxhPlus.h"

#include "HJSHelper.h"
#include "cocos2d_specifics.hpp"
#include "js_manual_conversions.h"

#include "../auto/jsb_cocos2dx_h_auto.hpp"

#include "h.h"
#include "msgpack.hpp"

USING_NS_CC_EXT;
USING_NS_CC_H;

#pragma mark - utility functions

extern bool JSB_dataptr_to_jsval_typedarray(JSContext *cx, jsval *vp, GLsizei count, void *data, JSArrayBufferViewType t);
namespace cocos2d {
    namespace h {
        extern void msgpack2js(std::string &ret, const msgpack::object o, bool asKey = false);
    }
}

extern bool jsval_to_int8(JSContext *cx, jsval vp, int8_t *ret);
extern bool jsval_to_uint8(JSContext *cx, jsval vp, uint8_t *ret);
extern bool jsval_to_int16(JSContext *cx, jsval vp, int16_t *ret);
extern bool jsval_to_int64(JSContext *cx, jsval vp, int64_t *ret);
extern bool jsval_to_uint64(JSContext *cx, jsval vp, uint64_t *ret);
extern bool jsval_to_string_vector(JSContext* cx, jsval v, std::vector<std::string>& ret);

extern jsval int8_to_jsval(JSContext* cx, int8_t v);
extern jsval uint8_to_jsval(JSContext* cx, uint8_t v);
extern jsval int16_to_jsval(JSContext* cx, int16_t v);
extern jsval uint16_to_jsval(JSContext* cx, uint16_t v);
extern jsval int64_to_jsval(JSContext* cx, int64_t v);
extern jsval uint64_to_jsval(JSContext* cx, uint64_t v);
extern jsval string_vector_to_jsval(JSContext* cx, const std::vector<std::string>& arr);

extern bool js_cocos2dx_retain(JSContext *cx, uint32_t argc, jsval *vp);
extern bool js_cocos2dx_release(JSContext *cx, uint32_t argc, jsval *vp);
extern bool js_cocos2dxh_autorelease(JSContext *cx, uint32_t argc, jsval *vp);

#pragma mark HAssetsManager

bool js_cocos2dx_h_HAssetsManager_readdir(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_readdir : Error processing arguments");
		std::vector<std::string> ret = cocos2d::h::HAssetsManager::readdir(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = string_vector_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	if (argc == 2) {
		std::string arg0;
		bool arg1;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
        arg1 = JSVAL_TO_BOOLEAN(argv[1]);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_readdir : Error processing arguments");
		std::vector<std::string> ret = cocos2d::h::HAssetsManager::readdir(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = string_vector_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_readdir : wrong number of arguments");
	return false;
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#pragma mark - HJSStoreProductWrapper

class HJSStoreProductWrapper :
public JSCallbackWrapper,
public HStoreProductsRequestDelegate {
public:
    void onRequestProductsCompleted(const vector<HStoreProduct*> &products, const vector<string> &invalidProductsId) override {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        const char *funcName = "onRequestProductsCompleted";
        if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            auto arr = cocos2d::Array::createWithCapacity(products.size());
            for (const auto &v : products) {
                auto dict = cocos2d::Dictionary::create();
                dict->setObject(cocos2d::String::create(v->getIdentifier()), "identifier");
                dict->setObject(cocos2d::String::create(v->getTitle()), "title");
                dict->setObject(cocos2d::String::create(v->getDescription()), "description");
                dict->setObject(cocos2d::Float::create(v->getPrice()), "price");
                dict->setObject(cocos2d::String::create(v->getPriceLocale()), "priceLocale");
                arr->addObject(dict);
            }
            
            jsval dataVal[2];
            dataVal[0] = ccarray_to_jsval(cx, arr);
            dataVal[1] = string_vector_to_jsval(cx, invalidProductsId);
            JS_AddValueRoot(cx, dataVal);
            
            JS_CallFunctionName(cx, obj, funcName, 2, dataVal, &retval);
            
            JS_RemoveValueRoot(cx, dataVal);
        }
    }
    void onRequestProductsFailed(HStore::ProductRequestError errorCode, const char *errorString) override {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        const char *funcName = "onRequestProductsFailed";
        if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            JSString *jsretErrorCode = JS_NewStringCopyZ(cx, errorString);
            
            jsval dataVal[2];
            dataVal[0] = INT_TO_JSVAL(static_cast<int32_t>(errorCode));
            dataVal[1] = STRING_TO_JSVAL(jsretErrorCode);
            
            JS_AddValueRoot(cx, dataVal);
            
            JS_CallFunctionName(cx, obj, funcName, 2, dataVal, &retval);
            
            JS_RemoveValueRoot(cx, dataVal);
        }
    }
};

#pragma mark - HJSStoreTransactionWrapper

class HJSStoreTransactionWrapper :
public JSCallbackWrapper,
public HStoreTransactionDelegate {
public:
    void onTransactionCompleted(HStorePaymentTransaction *transaction) override {
        processCallBack(transaction, "onTransactionCompleted");
    }
    void onTransactionFailed(HStorePaymentTransaction *transaction, int errorCode, const char *errorString) override {
        processCallBack(transaction, errorCode, errorString, "onTransactionFailed");
    }
    void onTransactionRestored(HStorePaymentTransaction *transaction) override {
        processCallBack(transaction, "onTransactionRestored");
    }
    void onRestoreCompletedTransactionsFailed(int errorCode, const char *errorString) override {
        processCallBack(errorCode, errorString, "onRestoreCompletedTransactionsFailed");
    }
    void onRestoreCompletedTransactionsFinished() override {
        processCallBack("onRestoreCompletedTransactionsFinished");
    }
private:
    void processCallBack(HStorePaymentTransaction* transaction, const char *INfuncType) {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        const char *funcName = INfuncType;
        if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            jsval dataVal[1];
            dataVal[0] = getJSObject(cx, transaction);
            
            JS_AddValueRoot(cx, dataVal);
            
            JS_CallFunctionName(cx, obj, funcName, 1, dataVal, &retval);
            
            JS_RemoveValueRoot(cx, dataVal);
            
            removeJSObject(cx, transaction);
        }
    }
    void processCallBack(HStorePaymentTransaction* transaction, int errorCode, const char *errorString, const char *INfuncType) {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        const char *funcName = INfuncType;
        if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            jsval dataVal[3];
            dataVal[0] = getJSObject(cx, transaction);
            dataVal[1] = INT_TO_JSVAL(errorCode);
            dataVal[2] = c_string_to_jsval(cx, errorString);
            
            JS_AddValueRoot(cx, dataVal);
            
            JS_CallFunctionName(cx, obj, funcName, 3, dataVal, &retval);
            
            JS_RemoveValueRoot(cx, dataVal);
            
            removeJSObject(cx, transaction);
        }
    }
    void processCallBack(const char *INfuncType) {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        const char *funcName = INfuncType;
        if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            JS_CallFunctionName(cx, obj, funcName, 0, nullptr, &retval);
        }
    }
    void processCallBack(int errorCode, const char *errorString, const char *INfuncType) {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        const char *funcName = INfuncType;
        if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            jsval dataVal[2];
            dataVal[0] = INT_TO_JSVAL(errorCode);
            dataVal[1] = c_string_to_jsval(cx, errorString);
            
            JS_AddValueRoot(cx, dataVal);
            
            JS_CallFunctionName(cx, obj, funcName, 2, dataVal, &retval);
            
            JS_RemoveValueRoot(cx, dataVal);
        }
    }
};

#pragma mark - HStore

bool js_cocos2dxh_HStore_setDelegate(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc >= 1) {
        jsval *argv = JS_ARGV(cx, vp);

        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        js_proxy_t *proxy;
        JS_GET_NATIVE_PROXY(proxy, obj);
        HStore *node = (HStore *)(proxy ? proxy->ptr : NULL);
        JSB_PRECONDITION2( node, cx, false, "js_cocos2dxh_HStore_setDelegate : Invalid Native Object");

        HJSStoreTransactionWrapper *tmpCobj = new HJSStoreTransactionWrapper();
        tmpCobj->autorelease();

        tmpCobj->setJSCallbackThis(argv[0]);
        
        node->setDelegate(tmpCobj);

        JS_SetReservedSlot(proxy->obj, 0, argv[0]);
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

bool js_cocos2dxh_HStore_loadProducts(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc >= 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        js_proxy_t *proxy;
        JS_GET_NATIVE_PROXY(proxy, obj);
        HStore *node = (HStore *)(proxy ? proxy->ptr : NULL);

        HJSStoreProductWrapper *tmpCobj = new HJSStoreProductWrapper();
        tmpCobj->autorelease();
        
        vector<string> arg0;
        jsval_to_string_vector(cx, argv[0], arg0);

        tmpCobj->setJSCallbackThis(argv[1]);
        node->loadProducts(arg0, tmpCobj);

        JS_SetReservedSlot(proxy->obj, 0, argv[0]);
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

#pragma mark - HStorePaymentTransaction

JSClass  *jsb_HStorePaymentTransaction_class;
JSObject *jsb_HStorePaymentTransaction_prototype;

bool js_cocos2dxh_HStorePaymentTransaction_getQuantity(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStorePaymentTransaction* cobj = (cocos2d::h::HStorePaymentTransaction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HStorePaymentTransaction_getQuantity : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getQuantity();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HStorePaymentTransaction_getQuantity : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HStorePaymentTransaction_getDateTime(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStorePaymentTransaction* cobj = (cocos2d::h::HStorePaymentTransaction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HStorePaymentTransaction_getDateTime : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->getDateTime();
		jsval jsret;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HStorePaymentTransaction_getDateTime : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HStorePaymentTransaction_getTransactionIdentifier(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStorePaymentTransaction* cobj = (cocos2d::h::HStorePaymentTransaction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HStorePaymentTransaction_getTransactionIdentifier : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getTransactionIdentifier();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HStorePaymentTransaction_getTransactionIdentifier : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HStorePaymentTransaction_getErrorCode(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStorePaymentTransaction* cobj = (cocos2d::h::HStorePaymentTransaction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HStorePaymentTransaction_getErrorCode : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getErrorCode();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HStorePaymentTransaction_getErrorCode : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HStorePaymentTransaction_getOriginalTransaction(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStorePaymentTransaction* cobj = (cocos2d::h::HStorePaymentTransaction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HStorePaymentTransaction_getOriginalTransaction : Invalid Native Object");
	if (argc == 0) {
		cocos2d::h::HStorePaymentTransaction* ret = cobj->getOriginalTransaction();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::h::HStorePaymentTransaction>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HStorePaymentTransaction_getOriginalTransaction : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HStorePaymentTransaction_getReceiptVerifyStatus(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStorePaymentTransaction* cobj = (cocos2d::h::HStorePaymentTransaction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HStorePaymentTransaction_getReceiptVerifyStatus : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getReceiptVerifyStatus();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HStorePaymentTransaction_getReceiptVerifyStatus : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HStorePaymentTransaction_getTransactionState(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStorePaymentTransaction* cobj = (cocos2d::h::HStorePaymentTransaction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HStorePaymentTransaction_getTransactionState : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getTransactionState();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HStorePaymentTransaction_getTransactionState : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HStorePaymentTransaction_getErrorDescription(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStorePaymentTransaction* cobj = (cocos2d::h::HStorePaymentTransaction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HStorePaymentTransaction_getErrorDescription : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getErrorDescription();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HStorePaymentTransaction_getErrorDescription : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HStorePaymentTransaction_getReceiptDataLength(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStorePaymentTransaction* cobj = (cocos2d::h::HStorePaymentTransaction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HStorePaymentTransaction_getReceiptDataLength : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getReceiptDataLength();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HStorePaymentTransaction_getReceiptDataLength : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HStorePaymentTransaction_getReceiptVerifyMode(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStorePaymentTransaction* cobj = (cocos2d::h::HStorePaymentTransaction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HStorePaymentTransaction_getReceiptVerifyMode : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getReceiptVerifyMode();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HStorePaymentTransaction_getReceiptVerifyMode : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HStorePaymentTransaction_getProductIdentifier(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStorePaymentTransaction* cobj = (cocos2d::h::HStorePaymentTransaction *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HStorePaymentTransaction_getProductIdentifier : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getProductIdentifier();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HStorePaymentTransaction_getProductIdentifier : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}



void js_cocos2dxh_HStorePaymentTransaction_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HStorePaymentTransaction)", obj);
}
static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return false;
}
static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
	vp.set(BOOLEAN_TO_JSVAL(true));
	return true;
}
void js_register_cocos2dxh_HStorePaymentTransaction(JSContext *cx, JSObject *global) {
	jsb_HStorePaymentTransaction_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_HStorePaymentTransaction_class->name = "HStorePaymentTransaction";
	jsb_HStorePaymentTransaction_class->addProperty = JS_PropertyStub;
	jsb_HStorePaymentTransaction_class->delProperty = JS_DeletePropertyStub;
	jsb_HStorePaymentTransaction_class->getProperty = JS_PropertyStub;
	jsb_HStorePaymentTransaction_class->setProperty = JS_StrictPropertyStub;
	jsb_HStorePaymentTransaction_class->enumerate = JS_EnumerateStub;
	jsb_HStorePaymentTransaction_class->resolve = JS_ResolveStub;
	jsb_HStorePaymentTransaction_class->convert = JS_ConvertStub;
	jsb_HStorePaymentTransaction_class->finalize = js_cocos2dxh_HStorePaymentTransaction_finalize;
	jsb_HStorePaymentTransaction_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};
    
	static JSFunctionSpec funcs[] = {
		JS_FN("getQuantity", js_cocos2dxh_HStorePaymentTransaction_getQuantity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getDateTime", js_cocos2dxh_HStorePaymentTransaction_getDateTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTransactionIdentifier", js_cocos2dxh_HStorePaymentTransaction_getTransactionIdentifier, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getErrorCode", js_cocos2dxh_HStorePaymentTransaction_getErrorCode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getOriginalTransaction", js_cocos2dxh_HStorePaymentTransaction_getOriginalTransaction, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getReceiptVerifyStatus", js_cocos2dxh_HStorePaymentTransaction_getReceiptVerifyStatus, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTransactionState", js_cocos2dxh_HStorePaymentTransaction_getTransactionState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getErrorDescription", js_cocos2dxh_HStorePaymentTransaction_getErrorDescription, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getReceiptDataLength", js_cocos2dxh_HStorePaymentTransaction_getReceiptDataLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getReceiptVerifyMode", js_cocos2dxh_HStorePaymentTransaction_getReceiptVerifyMode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getProductIdentifier", js_cocos2dxh_HStorePaymentTransaction_getProductIdentifier, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};
    
	JSFunctionSpec *st_funcs = NULL;
    
	jsb_HStorePaymentTransaction_prototype = JS_InitClass(
                                                          cx, global,
                                                          NULL, // parent proto
                                                          jsb_HStorePaymentTransaction_class,
                                                          empty_constructor, 0,
                                                          properties,
                                                          funcs,
                                                          NULL, // no static properties
                                                          st_funcs);
//	// make the class enumerable in the registered namespace
//	bool found;
//	JS_SetPropertyAttributes(cx, global, "HStorePaymentTransaction", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HStorePaymentTransaction> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_HStorePaymentTransaction_class;
		p->proto = jsb_HStorePaymentTransaction_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC

#pragma mark - HJSSocketWrapper

class HJSSocketWrapper :
public JSCallbackWrapper,
public HSocketDelegateBase {
public:
    void callbackConnected() override {
        processCallBack("onSocketConnected");
    }
    void callbackConnectFailed() override {
        processCallBack("onSocketConnectFailed");
    }
    void callbackDisconnected() override {
        processCallBack("onSocketDisconnected");
    }
    void callbackReceived(HPacketBase *INpacket) override {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        const char *funcName = "onSocketReceived";
        if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            jsval dataVal[1];
            dataVal[0] = getPacketJSValue(cx, INpacket);
            
            JS_AddValueRoot(cx, dataVal);
            
            JS_CallFunctionName(cx, obj, funcName, 1, dataVal, &retval);
            
            JS_RemoveValueRoot(cx, dataVal);
            
            removeJSObject(cx, INpacket);
        }
    }
private:
    virtual jsval getPacketJSValue(JSContext *cx, HPacketBase *INpacket) = 0;
private:
    void processCallBack(const char *INfuncName) {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        const char *funcName = INfuncName;
        if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            JS_CallFunctionName(cx, obj, funcName, 0, nullptr, &retval);
        }
    }
};

#pragma mark - HJSMSSocketWrapper

class HJSMSPacketFactoryWrapper
    : public HMSPacketFactory
, public cocos2d::Ref {};

class HJSMSSocketWrapper :
public HJSSocketWrapper {
private:
    jsval getPacketJSValue(JSContext *cx, HPacketBase *INpacket) override {
        auto packet = dynamic_cast<HMSPacket*>(INpacket);
        return getJSObject(cx, packet);
    }
};

#pragma mark - HJSBFSocketWrapper

class HJSBFPacketFactoryWrapper
: public HBFPacketFactory
, public cocos2d::Ref {};

class HJSBFSocketWrapper :
public HJSSocketWrapper {
private:
    jsval getPacketJSValue(JSContext *cx, HPacketBase *INpacket) override {
        auto packet = dynamic_cast<HBFPacket*>(INpacket);
        return getJSObject(cx, packet);
    }
};

#pragma mark - HJSWebViewWrapper

class HJSWebViewWrapper :
public JSCallbackWrapper,
public cocos2d::h::HWebViewDelegate {
public:
    bool webViewShouldStartLoadWithUrl(cocos2d::h::HWebView* INwebView, const char *INurl, cocos2d::h::HTUIWebViewNavigationType INtype) {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        const char *funcName = "onWebViewShouldStartLoadWithUrl";
        if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
                return false;
            }
            if(temp_retval == JSVAL_VOID) {
                return false;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            jsval dataVal[3];
            dataVal[0] = getJSObject(cx, INwebView);
            dataVal[1] = c_string_to_jsval(cx, INurl);
            dataVal[2] = int32_to_jsval(cx, INtype);
            
            JS_AddValueRoot(cx, dataVal);
            
            JS_CallFunctionName(cx, obj, funcName, 3, dataVal, &retval);
            
            JS_RemoveValueRoot(cx, dataVal);
            
            removeJSObject(cx, INwebView);
            return JSVAL_TO_BOOLEAN(retval);
        }
        return false;
    }
    void webViewDidStartLoad(cocos2d::h::HWebView* INwebView) {
        processCallBack(INwebView, "onWebViewDidStartLoad");
    }
    void webViewDidFinishLoad(cocos2d::h::HWebView* INwebView) {
        processCallBack(INwebView, "onWebViewDidFinishLoad");
    }
    void didFailLoad(cocos2d::h::HWebView* INwebView) {
        processCallBack(INwebView, "onDidFailLoad");
    }
private:
    void processCallBack(cocos2d::h::HWebView* INwebView, const char *INfuncName) {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        const char *funcName = INfuncName;
        if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            jsval dataVal[1];
            dataVal[0] = getJSObject(cx, INwebView);
            
            JS_AddValueRoot(cx, dataVal);
            
            JS_CallFunctionName(cx, obj, funcName, 1, dataVal, &retval);
            
            JS_RemoveValueRoot(cx, dataVal);
            
            removeJSObject(cx, INwebView);
        }
    }
};

#pragma mark - HJSHttpRequestWrapper

class HJSHttpRequestWrapper :
public JSCallbackWrapper,
public cocos2d::h::HHttpRequestDelegate {
public:
    void onReceiveHttpPacket(HHttpResponse *response) {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        const char *funcName = "onReceiveHttpPacket";
        if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            CCLOG("response coming...");
            CCLOG("%s", response->getResponseDataUnpacked().c_str());
            
            jsval dataVal[1];
            dataVal[0] = getJSObject(cx, response);
            
            JS_AddValueRoot(cx, dataVal);
            
            JS_CallFunctionName(cx, obj, funcName, 1, dataVal, &retval);
            
            JS_RemoveValueRoot(cx, dataVal);
            
            removeJSObject(cx, response);
        }
    }
};

#pragma mark - HJSAssetsManagerWrapper

class HJSAssetsManagerWrapper :
public JSCallbackWrapper,
public cocos2d::extension::AssetsManagerDelegateProtocol {
public:
    void onError(AssetsManager::ErrorCode errorCode) override {
        int param = static_cast<int>(errorCode);
        processCallback("onError", &param);
    }
    void onProgress(int percent) override {
        processCallback("onProgress", &percent);
    }
    void onSuccess() override {
        processCallback("onSuccess", nullptr);
    }
private:
    void processCallback(const char *func, int *param) {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        bool hasAction;
        JSObject *obj = JSVAL_TO_OBJECT(_jsThisObj);
        if (JS_HasProperty(cx, obj, func, &hasAction) && hasAction) {
            JS::RootedValue temp_retval(cx);
            if(!JS_GetProperty(cx, obj, func, &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JSAutoCompartment ac(cx, obj);
            
            if (param) {
                jsval dataVal[1];
                dataVal[0] = INT_TO_JSVAL(*param);
                
                JS_AddValueRoot(cx, dataVal);
                
                JS_CallFunctionName(cx, obj, func, 1, dataVal, &retval);
                
                JS_RemoveValueRoot(cx, dataVal);
            } else {
                JS_CallFunctionName(cx, obj, func, 0, nullptr, &retval);
            }
        }
    }
};

#pragma mark - cchGlobalFunction **************************

bool js_cocos2dxh_md5(JSContext *cx, uint32_t argc, jsval *vp) {
    jsval *argv = JS_ARGV(cx, vp);
	if (argc > 0) {
        const char *arg0;
        uint32_t arg1;
        int arg2 = -1;
        JSObject *jsobj;
        jsobj = JSVAL_TO_OBJECT(argv[0]);
        if (JS_IsTypedArrayObject(jsobj)) {
            JSArrayBufferViewType type = JS_GetArrayBufferViewType(jsobj);
            GLsizei count;
            JSB_jsval_typedarray_to_dataptr(cx, argv[0], &count, (void**)&arg0, type);
            arg1 = count;
        } else if (JS_IsArrayObject(cx, jsobj)) {
            GLsizei count;
            JSB_jsval_typedarray_to_dataptr(cx, argv[0], &count, (void**)&arg0, js::ArrayBufferView::TYPE_UINT32);
            arg1 = count;
        } else {
            jsval_to_charptr(cx, argv[0], &arg0);
            arg1 = strlen(arg0);
        }
        uint8_t output[16];
        if (argc > 1) {
            jsval_to_uint32(cx, argv[1], &arg1);
            if (argc > 2) {
                arg2 = JSVAL_TO_INT(argv[2]);
            }
        }
		HCrypto::md5(arg0, arg1, output);
        jsval jsret;
        if (arg2 == -1) {
            string str_ret = HCrypto::bin2hex(output, 16);
            jsret = std_string_to_jsval(cx, str_ret);
        } else {
            JSB_dataptr_to_jsval_typedarray(cx, &jsret, (GLsizei)16, output, (js::ArrayBufferView::ViewType)arg2);
        }
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dxh_generateUuid(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
        unsigned char ret[16] = {0};
        std::string hexStr = HNative::generateUuid();
        auto str = HCrypto::hex2bin(hexStr);
        memcpy(ret, str.data(), str.length());
        jsval jsret;
        JSB_dataptr_to_jsval_typedarray(cx, &jsret, (GLsizei)16, ret, js::ArrayBufferView::TYPE_UINT8);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dxh_gbktoutf8(JSContext *cx, uint32_t argc, jsval *vp) {
    jsval *argv = JS_ARGV(cx, vp);
	if (argc >= 1) {
        uint8_t *arg0;
        GLsizei count;
        JSB_jsval_typedarray_to_dataptr(cx, argv[0], &count, (void**)&arg0, js::ArrayBufferView::TYPE_UINT8);
        uint32_t arg1 = 256;
        if (argc > 1) {
            jsval_to_uint32(cx, argv[1], &arg1);
        }
        char *ret = new char[arg1];
        memset(ret, 0, arg1);
        HStringConverter::IConvConvert(Charset_UTF8, Charset_GBK2312, (const char*)arg0, count, ret, arg1);
        jsval jsret;
        JSB_dataptr_to_jsval_typedarray(cx, &jsret, (GLsizei)strlen(ret), ret, js::ArrayBufferView::TYPE_UINT8);
        delete[] ret;
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dxh_utf8togbk(JSContext *cx, uint32_t argc, jsval *vp) {
    jsval *argv = JS_ARGV(cx, vp);
	if (argc >= 1) {
        uint8_t *arg0;
        GLsizei count;
        JSB_jsval_typedarray_to_dataptr(cx, argv[0], &count, (void**)&arg0, js::ArrayBufferView::TYPE_UINT8);
        uint32_t arg1 = 256;
        if (argc > 1) {
            jsval_to_uint32(cx, argv[1], &arg1);
        }
        char *ret = new char[arg1];
        memset(ret, 0, arg1);
        HStringConverter::IConvConvert(Charset_GBK2312, Charset_UTF8, (const char*)arg0, count, ret, arg1);
        jsval jsret;
        JSB_dataptr_to_jsval_typedarray(cx, &jsret, (GLsizei)strlen(ret), ret, js::ArrayBufferView::TYPE_UINT8);
        delete[] ret;
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dxh_utf16toutf8(JSContext *cx, uint32_t argc, jsval *vp) {
    jsval *argv = JS_ARGV(cx, vp);
	if (argc == 1) {
        uint16_t *arg0;
        GLsizei count;
        JSB_jsval_typedarray_to_dataptr(cx, argv[0], &count, (void**)&arg0, js::ArrayBufferView::TYPE_UINT16);
        long items_read, items_write;
        char *ret = cocos2d::cc_utf16_to_utf8(arg0, count, &items_read, &items_write);
        jsval jsret;
        JSB_dataptr_to_jsval_typedarray(cx, &jsret, (GLsizei)items_write, ret, js::ArrayBufferView::TYPE_UINT8);
        delete[] ret;
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dxh_utf8toutf16(JSContext *cx, uint32_t argc, jsval *vp) {
    jsval *argv = JS_ARGV(cx, vp);
	if (argc == 1) {
        uint8_t *arg0;
        GLsizei count;
        JSB_jsval_typedarray_to_dataptr(cx, argv[0], &count, (void**)&arg0, js::ArrayBufferView::TYPE_UINT8);
        int rLen;
        uint16_t *ret = cocos2d::cc_utf8_to_utf16((const char*)arg0, count, &rLen);
        jsval jsret;
        JSB_dataptr_to_jsval_typedarray(cx, &jsret, (GLsizei)rLen, ret, js::ArrayBufferView::TYPE_UINT16);
        delete[] ret;
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dxh_uint8ArrayToFormatString(JSContext *cx, uint32_t argc, jsval *vp) {
    jsval *argv = JS_ARGV(cx, vp);
	if (argc == 2) {
        uint8_t *arg0;
        std::string arg1;
        GLsizei count;
        JSB_jsval_typedarray_to_dataptr(cx, argv[0], &count, (void**)&arg0, js::ArrayBufferView::TYPE_UINT8);
        jsval_to_std_string(cx, argv[1], &arg1);
        std::string ret;
        for (int i = 0; i < count; ++i) {
            char a[3];
            sprintf(a, arg1.c_str(), arg0[i]);
            ret += a;
        }
        jsval jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dxh_msgpack2js(JSContext *cx, uint32_t argc, jsval *vp) {
    jsval *argv = JS_ARGV(cx, vp);
	if (argc == 1) {
        string data;
        jsval_to_std_string(cx, argv[0], &data);
        msgpack::unpacker m_unpacker;
        auto size = data.length();
        m_unpacker.reserve_buffer(size);
        memcpy(m_unpacker.buffer(), data.data(), size);
        m_unpacker.buffer_consumed(size);
        
        string ret;
        msgpack::unpacked m_unpacked;
        while (m_unpacker.next(&m_unpacked)) {
            msgpack2js(ret, m_unpacked.get());
        }
        CCLOG("%s", ret.c_str());

        jsval jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

#pragma mark - HMSPacket

bool js_cocos2dxh_HMSPacket_readBool(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->readBool();
		jsval jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HMSPacket_readInt8(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		int8_t ret = cobj->readInt8();
		jsval jsret = int8_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HMSPacket_readUInt8(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		uint8_t ret = cobj->readUInt8();
		jsval jsret = uint8_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HMSPacket_readInt16(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		int16_t ret = cobj->readInt16();
		jsval jsret = int16_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HMSPacket_readUInt16(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		uint16_t ret = cobj->readUInt16();
		jsval jsret = uint16_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HMSPacket_readInt32(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		int32_t ret = cobj->readInt32();
		jsval jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HMSPacket_readUInt32(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		uint32_t ret = cobj->readUInt32();
		jsval jsret = uint32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HMSPacket_readInt64(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		int64_t ret = cobj->readInt64();
		jsval jsret = int64_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HMSPacket_readUInt64(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		uint64_t ret = cobj->readUInt64();
		jsval jsret = uint64_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HMSPacket_readFloat(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		float ret = cobj->readFloat();
		jsval jsret;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HMSPacket_readDouble(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->readDouble();
		jsval jsret;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dxh_HMSPacket_readString(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->readString();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_readBuffer(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
        std::string a = cobj->readBuffer();
		jsval jsret;
        JSB_dataptr_to_jsval_typedarray(cx, &jsret, (GLsizei)a.size(), (void*)a.data(), js::ArrayBufferView::TYPE_UINT8);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeBool(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		bool arg0 = JSVAL_TO_BOOLEAN(argv[0]);
		cobj->writeBool(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeInt8(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		int8_t arg0;
		ok &= jsval_to_int8(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		cobj->writeInt8(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeUInt8(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		uint8_t arg0;
		ok &= jsval_to_uint8(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		cobj->writeUInt8(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeInt16(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		int16_t arg0;
		ok &= jsval_to_int16(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		cobj->writeInt16(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeUInt16(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		uint16_t arg0;
        ok &= jsval_to_uint16(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		cobj->writeUInt16(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeInt32(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		int32_t arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		cobj->writeInt32(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeUInt32(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		uint32_t arg0;
		ok &= jsval_to_uint32(cx, argv[0], (uint32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		cobj->writeUInt32(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeInt64(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		int64_t arg0;
		ok &= jsval_to_int64(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		cobj->writeInt64(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeUInt64(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		uint64_t arg0;
        ok &= jsval_to_uint64(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		cobj->writeUInt64(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeFloat(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		double arg0;
        arg0 = JSVAL_TO_DOUBLE(argv[0]);
		cobj->writeFloat(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeDouble(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		double arg0;
        arg0 = JSVAL_TO_DOUBLE(argv[0]);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		cobj->writeDouble(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeString(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		cobj->writeString(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dxh_HMSPacket_writeBuffer(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc >= 1) {
		char* arg0;
        GLsizei count;
        ok &= JSB_jsval_typedarray_to_dataptr(cx, argv[0], &count, (void**)&arg0, js::ArrayBufferView::TYPE_UINT8);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        if (argc >= 2) {
            uint32_t arg1;
            jsval_to_uint32(cx, argv[1], &arg1);
            count = arg1;
        }
		cobj->writeBuffer(arg0, count);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dxh_HMSPacket_setCmdKey(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HMSPacket_setCmdKey : Invalid Native Object");
	if (argc == 1) {
		uint16_t arg0;
        ok = jsval_to_uint16(cx, argv[0], &arg0);
		cobj->setCmdKey(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HMSPacket_setCmdKey : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HMSPacket_getCmdKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dxh_HMSPacket_getCmdKey : Invalid Native Object");
	if (argc == 0) {
		uint16_t ret = cobj->getCmdKey();
		jsval jsret = uint16_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_cocos2dxh_HMSPacket_getCmdKey : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

#pragma mark - HSocket

bool js_cocos2dxh_HSocket_send(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::h::HSocket* cobj = (cocos2d::h::HSocket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::h::HMSPacket* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::h::HMSPacket*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		uint32_t ret = cobj->send(arg0);
		jsval jsret = uint32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dxh_HSocket_setDelegate(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc >= 2) {
		jsval *argv = JS_ARGV(cx, vp);
        
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
		js_proxy_t *proxy;
		JS_GET_NATIVE_PROXY(proxy, obj);
		HSocket *node = (HSocket *)(proxy ? proxy->ptr : NULL);
        
        std::string type;
        jsval_to_std_string(cx, argv[1], &type);
        if (type == "bf") {
            auto tmpCobj = new HJSBFSocketWrapper();
            tmpCobj->autorelease();
            tmpCobj->setJSCallbackThis(argv[0]);
            node->setSocketDelegate(tmpCobj);
            
            auto fac = new HJSBFPacketFactoryWrapper();
            fac->autorelease();
            node->setPacketFactory(fac);
        } else if (type == "moshuo") {
            auto tmpCobj = new HJSMSSocketWrapper();
            tmpCobj->autorelease();
            tmpCobj->setJSCallbackThis(argv[0]);
            node->setSocketDelegate(tmpCobj);
            
            auto fac = new HJSMSPacketFactoryWrapper();
            fac->autorelease();
            node->setPacketFactory(fac);
        }
        
        JS_SetReservedSlot(proxy->obj, 0, argv[0]);
        return true;
    }
    return false;
}

#pragma mark - HWebView

bool js_cocos2dxh_HWebView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc >= 1) {
		jsval *argv = JS_ARGV(cx, vp);
        
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
		js_proxy_t *proxy;
		JS_GET_NATIVE_PROXY(proxy, obj);
		HWebView *node = (HWebView *)(proxy ? proxy->ptr : NULL);
        
        HJSWebViewWrapper *tmpCobj = new HJSWebViewWrapper();
        tmpCobj->autorelease();
        
        tmpCobj->setJSCallbackThis(argv[0]);
        if(argc >= 1) {
            node->setDelegate(tmpCobj);
            
            JS_SetReservedSlot(proxy->obj, 0, argv[0]);
            return true;
        }
        JS_ReportError(cx, "wrong number of arguments");
        return true;
    }
    return false;
}

#pragma mark - HHttpRequest

bool js_cocos2dxh_HHttpRequest_setDelegate(JSContext *cx, uint32_t argc, jsval *vp) {
    if (argc >= 1) {
		jsval *argv = JS_ARGV(cx, vp);
        
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
		js_proxy_t *proxy;
		JS_GET_NATIVE_PROXY(proxy, obj);
		HHttpRequest *node = (HHttpRequest *)(proxy ? proxy->ptr : NULL);
        
        HJSHttpRequestWrapper *tmpCobj = new HJSHttpRequestWrapper();
        tmpCobj->autorelease();
        
        tmpCobj->setJSCallbackThis(argv[0]);
        if(argc >= 1) {
            node->setDelegate(tmpCobj);
            
            JS_SetReservedSlot(proxy->obj, 0, argv[0]);
            return true;
        }
        JS_ReportError(cx, "wrong number of arguments");
        return true;
    }
    return false;
}
bool js_cocos2dxh_HHttpRequest_setHeaders(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		vector<string> arg0;
        ok = jsval_to_string_vector(cx, argv[0], arg0);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		cobj->setHeaders(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

#pragma mark - register

void register_HJSCocos2dxhPlus(JSContext* cx, JSObject* global) {
    HJSHELPER_DEFINEFUNC_INIT("cch");
    
    JS_DefineFunction(cx, global, "md5", js_cocos2dxh_md5, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "generateUuid", js_cocos2dxh_generateUuid, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "gbktoutf8", js_cocos2dxh_gbktoutf8, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "utf8togbk", js_cocos2dxh_utf8togbk, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "utf16toutf8", js_cocos2dxh_utf16toutf8, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "utf8toutf16", js_cocos2dxh_utf8toutf16, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "uint8ArrayToFormatString", js_cocos2dxh_uint8ArrayToFormatString, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "msgpack2js", js_cocos2dxh_msgpack2js, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_cocos2d_h_HAssetsManager_prototype, "readdir", js_cocos2dx_h_HAssetsManager_readdir, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    JS_DefineFunction(cx, jsb_cocos2d_h_HStore_prototype, "setDelegate", js_cocos2dxh_HStore_setDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HStore_prototype, "loadProducts", js_cocos2dxh_HStore_loadProducts, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    js_register_cocos2dxh_HStorePaymentTransaction(cx, global);
#endif
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "retain", js_cocos2dx_retain, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "release", js_cocos2dx_release, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "autorelease", js_cocos2dxh_autorelease, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readBool", js_cocos2dxh_HMSPacket_readBool, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readInt8", js_cocos2dxh_HMSPacket_readInt8, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readUInt8", js_cocos2dxh_HMSPacket_readUInt8, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readInt16", js_cocos2dxh_HMSPacket_readInt16, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readUInt16", js_cocos2dxh_HMSPacket_readUInt16, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readInt32", js_cocos2dxh_HMSPacket_readInt32, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readUInt32", js_cocos2dxh_HMSPacket_readUInt32, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readInt64", js_cocos2dxh_HMSPacket_readInt64, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readUInt64", js_cocos2dxh_HMSPacket_readUInt64, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readFloat", js_cocos2dxh_HMSPacket_readFloat, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readDouble", js_cocos2dxh_HMSPacket_readDouble, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readString", js_cocos2dxh_HMSPacket_readString, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "readBuffer", js_cocos2dxh_HMSPacket_readBuffer, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeBool", js_cocos2dxh_HMSPacket_writeBool, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeInt8", js_cocos2dxh_HMSPacket_writeInt8, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeUInt8", js_cocos2dxh_HMSPacket_writeUInt8, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeInt16", js_cocos2dxh_HMSPacket_writeInt16, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeUInt16", js_cocos2dxh_HMSPacket_writeUInt16, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeInt32", js_cocos2dxh_HMSPacket_writeInt32, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeUInt32", js_cocos2dxh_HMSPacket_writeUInt32, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeInt64", js_cocos2dxh_HMSPacket_writeInt64, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeUInt64", js_cocos2dxh_HMSPacket_writeUInt64, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeFloat", js_cocos2dxh_HMSPacket_writeFloat, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeDouble", js_cocos2dxh_HMSPacket_writeDouble, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeString", js_cocos2dxh_HMSPacket_writeString, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "writeBuffer", js_cocos2dxh_HMSPacket_writeBuffer, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "setCmdKey", js_cocos2dxh_HMSPacket_setCmdKey, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HMSPacket_prototype, "getCmdKey", js_cocos2dxh_HMSPacket_getCmdKey, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_cocos2d_h_HSocket_prototype, "retain", js_cocos2dx_retain, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HSocket_prototype, "release", js_cocos2dx_release, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HSocket_prototype, "autorelease", js_cocos2dxh_autorelease, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HSocket_prototype, "setDelegate", js_cocos2dxh_HSocket_setDelegate, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HSocket_prototype, "send", js_cocos2dxh_HSocket_send, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_cocos2d_h_HWebView_prototype, "setDelegate", js_cocos2dxh_HWebView_setDelegate, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_cocos2d_h_HHttpRequest_prototype, "retain", js_cocos2dx_retain, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HHttpRequest_prototype, "release", js_cocos2dx_release, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HHttpRequest_prototype, "setDelegate", js_cocos2dxh_HHttpRequest_setDelegate, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_h_HHttpRequest_prototype, "setHeaders", js_cocos2dxh_HHttpRequest_setHeaders, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}
