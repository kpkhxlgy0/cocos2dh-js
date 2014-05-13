#include "jsb_cocos2dx_h_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "h.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JSObject* global = ScriptingCore::getInstance()->getGlobalObject();
	isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && JSVAL_TO_BOOLEAN(initializing);
	if (isNewValid)
	{
		TypeTest<T> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");

		JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
		return true;
	}

    JS_ReportError(cx, "Don't use `new cc.XXX`, please use `cc.XXX.create` instead! ");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
	vp.set(BOOLEAN_TO_JSVAL(true));
	return true;	
}
JSClass  *jsb_cocos2d_h_HNative_class;
JSObject *jsb_cocos2d_h_HNative_prototype;

bool js_cocos2dx_h_HNative_addAlertButton(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HNative_addAlertButton : Error processing arguments");
		int ret = cocos2d::h::HNative::addAlertButton(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_addAlertButton : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNative_openURL(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HNative_openURL : Error processing arguments");
		cocos2d::h::HNative::openURL(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_openURL : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNative_showActivityIndicator(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::h::HNative::showActivityIndicator();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_showActivityIndicator : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNative_hideActivityIndicator(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::h::HNative::hideActivityIndicator();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_hideActivityIndicator : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNative_getDeviceName(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		const std::string ret = cocos2d::h::HNative::getDeviceName();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_getDeviceName : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNative_vibrate(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::h::HNative::vibrate();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_vibrate : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNative_generateUuid(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		std::string ret = cocos2d::h::HNative::generateUuid();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_generateUuid : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNative_getInputText(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 3) {
		const char* arg0;
		const char* arg1;
		const char* arg2;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HNative_getInputText : Error processing arguments");
		const std::string ret = cocos2d::h::HNative::getInputText(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_getInputText : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNative_cancelAlert(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::h::HNative::cancelAlert();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_cancelAlert : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNative_showAlert(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 0) {
		cocos2d::h::HNative::showAlert();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	if (argc == 1) {
		cocos2d::h::HAlertViewDelegate* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::h::HAlertViewDelegate*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HNative_showAlert : Error processing arguments");
		cocos2d::h::HNative::showAlert(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_showAlert : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNative_getOpenUDID(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		const std::string ret = cocos2d::h::HNative::getOpenUDID();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_getOpenUDID : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNative_createAlert(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 3) {
		const char* arg0;
		const char* arg1;
		const char* arg2;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HNative_createAlert : Error processing arguments");
		cocos2d::h::HNative::createAlert(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNative_createAlert : wrong number of arguments");
	return false;
}



void js_cocos2d_h_HNative_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HNative)", obj);
}

void js_register_cocos2dx_h_HNative(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HNative_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HNative_class->name = "HNative";
	jsb_cocos2d_h_HNative_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HNative_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HNative_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HNative_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HNative_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HNative_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HNative_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HNative_class->finalize = js_cocos2d_h_HNative_finalize;
	jsb_cocos2d_h_HNative_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("addAlertButton", js_cocos2dx_h_HNative_addAlertButton, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("openURL", js_cocos2dx_h_HNative_openURL, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("showActivityIndicator", js_cocos2dx_h_HNative_showActivityIndicator, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("hideActivityIndicator", js_cocos2dx_h_HNative_hideActivityIndicator, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getDeviceName", js_cocos2dx_h_HNative_getDeviceName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("vibrate", js_cocos2dx_h_HNative_vibrate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("generateUuid", js_cocos2dx_h_HNative_generateUuid, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInputText", js_cocos2dx_h_HNative_getInputText, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("cancelAlert", js_cocos2dx_h_HNative_cancelAlert, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("showAlert", js_cocos2dx_h_HNative_showAlert, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getOpenUDID", js_cocos2dx_h_HNative_getOpenUDID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createAlert", js_cocos2dx_h_HNative_createAlert, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HNative_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HNative_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HNative", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HNative> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HNative_class;
		p->proto = jsb_cocos2d_h_HNative_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HBFPacket_class;
JSObject *jsb_cocos2d_h_HBFPacket_prototype;

bool js_cocos2dx_h_HBFPacket_writeString(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HBFPacket* cobj = (cocos2d::h::HBFPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HBFPacket_writeString : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HBFPacket_writeString : Error processing arguments");
		cobj->writeString(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HBFPacket_writeString : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HBFPacket_beginWrite(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HBFPacket* cobj = (cocos2d::h::HBFPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HBFPacket_beginWrite : Invalid Native Object");
	if (argc == 0) {
		cobj->beginWrite();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HBFPacket_beginWrite : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HBFPacket_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HBFPacket* cobj = (cocos2d::h::HBFPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HBFPacket_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HBFPacket_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HBFPacket_readString(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HBFPacket* cobj = (cocos2d::h::HBFPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HBFPacket_readString : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->readString();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HBFPacket_readString : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HBFPacket_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::h::HBFPacket* ret = cocos2d::h::HBFPacket::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HBFPacket>(cx, (cocos2d::h::HBFPacket*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HBFPacket_create : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HBFPacket_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    cocos2d::h::HBFPacket* cobj = new cocos2d::h::HBFPacket();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::h::HBFPacket> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::h::HBFPacket");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_cocos2d_h_HBFPacket_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HBFPacket)", obj);
}

void js_register_cocos2dx_h_HBFPacket(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HBFPacket_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HBFPacket_class->name = "HBFPacket";
	jsb_cocos2d_h_HBFPacket_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HBFPacket_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HBFPacket_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HBFPacket_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HBFPacket_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HBFPacket_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HBFPacket_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HBFPacket_class->finalize = js_cocos2d_h_HBFPacket_finalize;
	jsb_cocos2d_h_HBFPacket_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("writeString", js_cocos2dx_h_HBFPacket_writeString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("beginWrite", js_cocos2dx_h_HBFPacket_beginWrite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_cocos2dx_h_HBFPacket_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("readString", js_cocos2dx_h_HBFPacket_readString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_h_HBFPacket_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HBFPacket_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HBFPacket_class,
		js_cocos2dx_h_HBFPacket_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HBFPacket", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HBFPacket> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HBFPacket_class;
		p->proto = jsb_cocos2d_h_HBFPacket_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HMSPacket_class;
JSObject *jsb_cocos2d_h_HMSPacket_prototype;

bool js_cocos2dx_h_HMSPacket_setRoute(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HMSPacket_setRoute : Invalid Native Object");
	if (argc == 1) {
		unsigned int arg0;
		ok &= jsval_to_uint32(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HMSPacket_setRoute : Error processing arguments");
		cobj->setRoute(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HMSPacket_setRoute : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HMSPacket_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HMSPacket_init : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HMSPacket_init : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HMSPacket_beginWrite(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HMSPacket_beginWrite : Invalid Native Object");
	if (argc == 0) {
		cobj->beginWrite();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HMSPacket_beginWrite : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HMSPacket_getRoute(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HMSPacket* cobj = (cocos2d::h::HMSPacket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HMSPacket_getRoute : Invalid Native Object");
	if (argc == 0) {
		unsigned int ret = cobj->getRoute();
		jsval jsret = JSVAL_NULL;
		jsret = uint32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HMSPacket_getRoute : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HMSPacket_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::h::HMSPacket* ret = cocos2d::h::HMSPacket::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HMSPacket>(cx, (cocos2d::h::HMSPacket*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HMSPacket_create : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HMSPacket_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    cocos2d::h::HMSPacket* cobj = new cocos2d::h::HMSPacket();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::h::HMSPacket> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::h::HMSPacket");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_cocos2d_h_HMSPacket_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HMSPacket)", obj);
}

void js_register_cocos2dx_h_HMSPacket(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HMSPacket_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HMSPacket_class->name = "HMSPacket";
	jsb_cocos2d_h_HMSPacket_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HMSPacket_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HMSPacket_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HMSPacket_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HMSPacket_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HMSPacket_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HMSPacket_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HMSPacket_class->finalize = js_cocos2d_h_HMSPacket_finalize;
	jsb_cocos2d_h_HMSPacket_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setRoute", js_cocos2dx_h_HMSPacket_setRoute, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_cocos2dx_h_HMSPacket_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("beginWrite", js_cocos2dx_h_HMSPacket_beginWrite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getRoute", js_cocos2dx_h_HMSPacket_getRoute, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_h_HMSPacket_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HMSPacket_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HMSPacket_class,
		js_cocos2dx_h_HMSPacket_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HMSPacket", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HMSPacket> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HMSPacket_class;
		p->proto = jsb_cocos2d_h_HMSPacket_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HAssetsManager_class;
JSObject *jsb_cocos2d_h_HAssetsManager_prototype;

bool js_cocos2dx_h_HAssetsManager_setStoragePath(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_setStoragePath : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_setStoragePath : Error processing arguments");
		cobj->setStoragePath(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_setStoragePath : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_getDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_getDelegate : Invalid Native Object");
	if (argc == 0) {
		cocos2d::h::HAssetsManagerDelegateProtocol* ret = cobj->getDelegate();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HAssetsManagerDelegateProtocol>(cx, (cocos2d::h::HAssetsManagerDelegateProtocol*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_getDelegate : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_checkUpdate(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_checkUpdate : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->checkUpdate();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_checkUpdate : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_getStoragePath(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_getStoragePath : Invalid Native Object");
	if (argc == 0) {
		const std::string& ret = cobj->getStoragePath();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_getStoragePath : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_getVersionRemote(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_getVersionRemote : Invalid Native Object");
	if (argc == 0) {
		const std::string& ret = cobj->getVersionRemote();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_getVersionRemote : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_update(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_update : Invalid Native Object");
	if (argc == 0) {
		cobj->update();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_update : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_setVersionFileUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_setVersionFileUrl : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_setVersionFileUrl : Error processing arguments");
		cobj->setVersionFileUrl(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_setVersionFileUrl : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_getConnectionTimeout(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_getConnectionTimeout : Invalid Native Object");
	if (argc == 0) {
		long ret = cobj->getConnectionTimeout();
		jsval jsret = JSVAL_NULL;
		jsret = long_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_getConnectionTimeout : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_getVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_getVersion : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getVersion();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_getVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_getVersionFileUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_getVersionFileUrl : Invalid Native Object");
	if (argc == 0) {
		const std::string& ret = cobj->getVersionFileUrl();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_getVersionFileUrl : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_setConnectionTimeout(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_setConnectionTimeout : Invalid Native Object");
	if (argc == 1) {
		long arg0;
		ok &= jsval_to_long(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_setConnectionTimeout : Error processing arguments");
		cobj->setConnectionTimeout(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_setConnectionTimeout : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_setVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HAssetsManager_setVersion : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_setVersion : Error processing arguments");
		cobj->setVersion(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_setVersion : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HAssetsManager_changeExt(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = true; break; }
			std::string ret = cocos2d::h::HAssetsManager::changeExt(arg0);
			jsval jsret = JSVAL_NULL;
			jsret = std_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 2) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = true; break; }
			std::string arg1;
			ok &= jsval_to_std_string(cx, argv[1], &arg1);
			if (!ok) { ok = true; break; }
			std::string ret = cocos2d::h::HAssetsManager::changeExt(arg0, arg1);
			jsval jsret = JSVAL_NULL;
			jsret = std_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_changeExt : wrong number of arguments");
	return false;
}
bool js_cocos2dx_h_HAssetsManager_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 7) {
		std::string arg0;
		std::string arg1;
		std::function<void (bool)> arg2;
		std::function<void ()> arg3;
		std::function<void (int)> arg4;
		std::function<void (int)> arg5;
		std::function<void ()> arg6;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[2]));
			auto lambda = [=](bool larg0) -> void {
				jsval largv[1];
				largv[0] = BOOLEAN_TO_JSVAL(larg0);
				jsval rval;
				bool ok = func->invoke(1, &largv[0], rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg2 = lambda;
		} while(0)
		;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[3]));
			auto lambda = [=]() -> void {
				jsval rval;
				bool ok = func->invoke(0, nullptr, rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg3 = lambda;
		} while(0)
		;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[4]));
			auto lambda = [=](int larg0) -> void {
				jsval largv[1];
				largv[0] = int32_to_jsval(cx, larg0);
				jsval rval;
				bool ok = func->invoke(1, &largv[0], rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg4 = lambda;
		} while(0)
		;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[5]));
			auto lambda = [=](int larg0) -> void {
				jsval largv[1];
				largv[0] = int32_to_jsval(cx, larg0);
				jsval rval;
				bool ok = func->invoke(1, &largv[0], rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg5 = lambda;
		} while(0)
		;
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[6]));
			auto lambda = [=]() -> void {
				jsval rval;
				bool ok = func->invoke(0, nullptr, rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg6 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_create : Error processing arguments");
		cocos2d::h::HAssetsManager* ret = cocos2d::h::HAssetsManager::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HAssetsManager>(cx, (cocos2d::h::HAssetsManager*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_create : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HAssetsManager_mkdir(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_mkdir : Error processing arguments");
		bool ret = cocos2d::h::HAssetsManager::mkdir(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_mkdir : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HAssetsManager_extname(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_extname : Error processing arguments");
		std::string ret = cocos2d::h::HAssetsManager::extname(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_extname : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HAssetsManager_isDirectory(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_isDirectory : Error processing arguments");
		bool ret = cocos2d::h::HAssetsManager::isDirectory(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_isDirectory : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HAssetsManager_rmdir(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_rmdir : Error processing arguments");
		bool ret = cocos2d::h::HAssetsManager::rmdir(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_rmdir : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HAssetsManager_dirname(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_dirname : Error processing arguments");
		std::string ret = cocos2d::h::HAssetsManager::dirname(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_dirname : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HAssetsManager_basename(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_basename : Error processing arguments");
		std::string ret = cocos2d::h::HAssetsManager::basename(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	if (argc == 2) {
		std::string arg0;
		std::string arg1;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HAssetsManager_basename : Error processing arguments");
		std::string ret = cocos2d::h::HAssetsManager::basename(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HAssetsManager_basename : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HAssetsManager_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    cocos2d::h::HAssetsManager* cobj = new cocos2d::h::HAssetsManager();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::h::HAssetsManager> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::h::HAssetsManager");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_cocos2d_h_HAssetsManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HAssetsManager)", obj);
}

void js_register_cocos2dx_h_HAssetsManager(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HAssetsManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HAssetsManager_class->name = "HAssetsManager";
	jsb_cocos2d_h_HAssetsManager_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HAssetsManager_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HAssetsManager_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HAssetsManager_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HAssetsManager_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HAssetsManager_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HAssetsManager_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HAssetsManager_class->finalize = js_cocos2d_h_HAssetsManager_finalize;
	jsb_cocos2d_h_HAssetsManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setStoragePath", js_cocos2dx_h_HAssetsManager_setStoragePath, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getDelegate", js_cocos2dx_h_HAssetsManager_getDelegate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("checkUpdate", js_cocos2dx_h_HAssetsManager_checkUpdate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStoragePath", js_cocos2dx_h_HAssetsManager_getStoragePath, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getVersionRemote", js_cocos2dx_h_HAssetsManager_getVersionRemote, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("update", js_cocos2dx_h_HAssetsManager_update, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setVersionFileUrl", js_cocos2dx_h_HAssetsManager_setVersionFileUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getConnectionTimeout", js_cocos2dx_h_HAssetsManager_getConnectionTimeout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getVersion", js_cocos2dx_h_HAssetsManager_getVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getVersionFileUrl", js_cocos2dx_h_HAssetsManager_getVersionFileUrl, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setConnectionTimeout", js_cocos2dx_h_HAssetsManager_setConnectionTimeout, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setVersion", js_cocos2dx_h_HAssetsManager_setVersion, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("changeExt", js_cocos2dx_h_HAssetsManager_changeExt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("create", js_cocos2dx_h_HAssetsManager_create, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("mkdir", js_cocos2dx_h_HAssetsManager_mkdir, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("extname", js_cocos2dx_h_HAssetsManager_extname, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isDirectory", js_cocos2dx_h_HAssetsManager_isDirectory, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("rmdir", js_cocos2dx_h_HAssetsManager_rmdir, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("dirname", js_cocos2dx_h_HAssetsManager_dirname, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("basename", js_cocos2dx_h_HAssetsManager_basename, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HAssetsManager_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_Node_prototype,
		jsb_cocos2d_h_HAssetsManager_class,
		js_cocos2dx_h_HAssetsManager_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HAssetsManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HAssetsManager> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HAssetsManager_class;
		p->proto = jsb_cocos2d_h_HAssetsManager_prototype;
		p->parentProto = jsb_cocos2d_Node_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HHttpPacker_class;
JSObject *jsb_cocos2d_h_HHttpPacker_prototype;

bool js_cocos2dx_h_HHttpPacker_getBase64(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpPacker* cobj = (cocos2d::h::HHttpPacker *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpPacker_getBase64 : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getBase64();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpPacker_getBase64 : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpPacker_packBoolean(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpPacker* cobj = (cocos2d::h::HHttpPacker *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpPacker_packBoolean : Invalid Native Object");
	if (argc == 1) {
		bool arg0;
		arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpPacker_packBoolean : Error processing arguments");
		cobj->packBoolean(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpPacker_packBoolean : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HHttpPacker_packArray(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpPacker* cobj = (cocos2d::h::HHttpPacker *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpPacker_packArray : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpPacker_packArray : Error processing arguments");
		cobj->packArray(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpPacker_packArray : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HHttpPacker_packMap(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpPacker* cobj = (cocos2d::h::HHttpPacker *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpPacker_packMap : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpPacker_packMap : Error processing arguments");
		cobj->packMap(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpPacker_packMap : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HHttpPacker_getStrEncoded(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpPacker* cobj = (cocos2d::h::HHttpPacker *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpPacker_getStrEncoded : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getStrEncoded();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpPacker_getStrEncoded : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpPacker_packString(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpPacker* cobj = (cocos2d::h::HHttpPacker *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpPacker_packString : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpPacker_packString : Error processing arguments");
		cobj->packString(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpPacker_packString : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HHttpPacker_packInteger(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpPacker* cobj = (cocos2d::h::HHttpPacker *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpPacker_packInteger : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpPacker_packInteger : Error processing arguments");
		cobj->packInteger(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpPacker_packInteger : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HHttpPacker_packDouble(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpPacker* cobj = (cocos2d::h::HHttpPacker *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpPacker_packDouble : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpPacker_packDouble : Error processing arguments");
		cobj->packDouble(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpPacker_packDouble : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HHttpPacker_packNil(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpPacker* cobj = (cocos2d::h::HHttpPacker *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpPacker_packNil : Invalid Native Object");
	if (argc == 0) {
		cobj->packNil();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpPacker_packNil : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpPacker_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::h::HHttpPacker* ret = cocos2d::h::HHttpPacker::create();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HHttpPacker>(cx, (cocos2d::h::HHttpPacker*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HHttpPacker_create : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HHttpPacker_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    cocos2d::h::HHttpPacker* cobj = new cocos2d::h::HHttpPacker();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::h::HHttpPacker> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::h::HHttpPacker");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_cocos2d_h_HHttpPacker_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HHttpPacker)", obj);
}

void js_register_cocos2dx_h_HHttpPacker(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HHttpPacker_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HHttpPacker_class->name = "HHttpPacker";
	jsb_cocos2d_h_HHttpPacker_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HHttpPacker_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HHttpPacker_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HHttpPacker_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HHttpPacker_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HHttpPacker_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HHttpPacker_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HHttpPacker_class->finalize = js_cocos2d_h_HHttpPacker_finalize;
	jsb_cocos2d_h_HHttpPacker_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getBase64", js_cocos2dx_h_HHttpPacker_getBase64, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("packBoolean", js_cocos2dx_h_HHttpPacker_packBoolean, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("packArray", js_cocos2dx_h_HHttpPacker_packArray, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("packMap", js_cocos2dx_h_HHttpPacker_packMap, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStrEncoded", js_cocos2dx_h_HHttpPacker_getStrEncoded, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("packString", js_cocos2dx_h_HHttpPacker_packString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("packInteger", js_cocos2dx_h_HHttpPacker_packInteger, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("packDouble", js_cocos2dx_h_HHttpPacker_packDouble, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("packNil", js_cocos2dx_h_HHttpPacker_packNil, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_h_HHttpPacker_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HHttpPacker_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HHttpPacker_class,
		js_cocos2dx_h_HHttpPacker_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HHttpPacker", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HHttpPacker> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HHttpPacker_class;
		p->proto = jsb_cocos2d_h_HHttpPacker_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HHttpRequest_class;
JSObject *jsb_cocos2d_h_HHttpRequest_prototype;

bool js_cocos2dx_h_HHttpRequest_addDataParam(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpRequest_addDataParam : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		std::string arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpRequest_addDataParam : Error processing arguments");
		cobj->addDataParam(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_addDataParam : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dx_h_HHttpRequest_setTimeoutForConnect(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpRequest_setTimeoutForConnect : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpRequest_setTimeoutForConnect : Error processing arguments");
		cobj->setTimeoutForConnect(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_setTimeoutForConnect : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HHttpRequest_addPackerParam(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpRequest_addPackerParam : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		cocos2d::h::HHttpPacker* arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::h::HHttpPacker*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpRequest_addPackerParam : Error processing arguments");
		cobj->addPackerParam(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_addPackerParam : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dx_h_HHttpRequest_getTimeoutForRead(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpRequest_getTimeoutForRead : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getTimeoutForRead();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_getTimeoutForRead : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpRequest_setTimeoutForRead(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpRequest_setTimeoutForRead : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpRequest_setTimeoutForRead : Error processing arguments");
		cobj->setTimeoutForRead(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_setTimeoutForRead : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HHttpRequest_setUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpRequest_setUrl : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpRequest_setUrl : Error processing arguments");
		cobj->setUrl(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_setUrl : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HHttpRequest_addData(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpRequest_addData : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		std::string arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpRequest_addData : Error processing arguments");
		cobj->addData(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_addData : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dx_h_HHttpRequest_setRequestType(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpRequest_setRequestType : Invalid Native Object");
	if (argc == 1) {
		cocos2d::network::HttpRequest::Type arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpRequest_setRequestType : Error processing arguments");
		cobj->setRequestType(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_setRequestType : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HHttpRequest_getTimeoutForConnect(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpRequest_getTimeoutForConnect : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getTimeoutForConnect();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_getTimeoutForConnect : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpRequest_send(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpRequest_send : Invalid Native Object");
	if (argc == 0) {
		cobj->send();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_send : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpRequest_addPacker(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpRequest* cobj = (cocos2d::h::HHttpRequest *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpRequest_addPacker : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		cocos2d::h::HHttpPacker* arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		do {
			if (!argv[1].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::h::HHttpPacker*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpRequest_addPacker : Error processing arguments");
		cobj->addPacker(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_addPacker : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dx_h_HHttpRequest_encodeUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpRequest_encodeUrl : Error processing arguments");
		std::string ret = cocos2d::h::HHttpRequest::encodeUrl(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_encodeUrl : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HHttpRequest_decodeUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HHttpRequest_decodeUrl : Error processing arguments");
		std::string ret = cocos2d::h::HHttpRequest::decodeUrl(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HHttpRequest_decodeUrl : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HHttpRequest_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    cocos2d::h::HHttpRequest* cobj = new cocos2d::h::HHttpRequest();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::h::HHttpRequest> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::h::HHttpRequest");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_cocos2d_h_HHttpRequest_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HHttpRequest)", obj);
}

void js_register_cocos2dx_h_HHttpRequest(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HHttpRequest_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HHttpRequest_class->name = "HHttpRequest";
	jsb_cocos2d_h_HHttpRequest_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HHttpRequest_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HHttpRequest_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HHttpRequest_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HHttpRequest_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HHttpRequest_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HHttpRequest_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HHttpRequest_class->finalize = js_cocos2d_h_HHttpRequest_finalize;
	jsb_cocos2d_h_HHttpRequest_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("addDataParam", js_cocos2dx_h_HHttpRequest_addDataParam, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTimeoutForConnect", js_cocos2dx_h_HHttpRequest_setTimeoutForConnect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addPackerParam", js_cocos2dx_h_HHttpRequest_addPackerParam, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTimeoutForRead", js_cocos2dx_h_HHttpRequest_getTimeoutForRead, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setTimeoutForRead", js_cocos2dx_h_HHttpRequest_setTimeoutForRead, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setUrl", js_cocos2dx_h_HHttpRequest_setUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addData", js_cocos2dx_h_HHttpRequest_addData, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setRequestType", js_cocos2dx_h_HHttpRequest_setRequestType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getTimeoutForConnect", js_cocos2dx_h_HHttpRequest_getTimeoutForConnect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("send", js_cocos2dx_h_HHttpRequest_send, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addPacker", js_cocos2dx_h_HHttpRequest_addPacker, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("encodeUrl", js_cocos2dx_h_HHttpRequest_encodeUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("decodeUrl", js_cocos2dx_h_HHttpRequest_decodeUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HHttpRequest_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HHttpRequest_class,
		js_cocos2dx_h_HHttpRequest_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HHttpRequest", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HHttpRequest> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HHttpRequest_class;
		p->proto = jsb_cocos2d_h_HHttpRequest_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HHttpResponse_class;
JSObject *jsb_cocos2d_h_HHttpResponse_prototype;

bool js_cocos2dx_h_HHttpResponse_getErrorBuffer(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpResponse* cobj = (cocos2d::h::HHttpResponse *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpResponse_getErrorBuffer : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getErrorBuffer();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpResponse_getErrorBuffer : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpResponse_getResponseDataUnpacked(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpResponse* cobj = (cocos2d::h::HHttpResponse *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpResponse_getResponseDataUnpacked : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getResponseDataUnpacked();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpResponse_getResponseDataUnpacked : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpResponse_isSucceed(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpResponse* cobj = (cocos2d::h::HHttpResponse *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpResponse_isSucceed : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isSucceed();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpResponse_isSucceed : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpResponse_getResponseCode(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpResponse* cobj = (cocos2d::h::HHttpResponse *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpResponse_getResponseCode : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getResponseCode();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpResponse_getResponseCode : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpResponse_getRequest(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpResponse* cobj = (cocos2d::h::HHttpResponse *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpResponse_getRequest : Invalid Native Object");
	if (argc == 0) {
		cocos2d::h::HHttpRequest* ret = cobj->getRequest();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HHttpRequest>(cx, (cocos2d::h::HHttpRequest*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpResponse_getRequest : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpResponse_getResponseHeader(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpResponse* cobj = (cocos2d::h::HHttpResponse *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpResponse_getResponseHeader : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getResponseHeader();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpResponse_getResponseHeader : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HHttpResponse_getResponseData(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HHttpResponse* cobj = (cocos2d::h::HHttpResponse *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HHttpResponse_getResponseData : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getResponseData();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HHttpResponse_getResponseData : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}


void js_cocos2d_h_HHttpResponse_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HHttpResponse)", obj);
}

void js_register_cocos2dx_h_HHttpResponse(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HHttpResponse_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HHttpResponse_class->name = "HHttpResponse";
	jsb_cocos2d_h_HHttpResponse_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HHttpResponse_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HHttpResponse_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HHttpResponse_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HHttpResponse_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HHttpResponse_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HHttpResponse_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HHttpResponse_class->finalize = js_cocos2d_h_HHttpResponse_finalize;
	jsb_cocos2d_h_HHttpResponse_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getErrorBuffer", js_cocos2dx_h_HHttpResponse_getErrorBuffer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getResponseDataUnpacked", js_cocos2dx_h_HHttpResponse_getResponseDataUnpacked, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isSucceed", js_cocos2dx_h_HHttpResponse_isSucceed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getResponseCode", js_cocos2dx_h_HHttpResponse_getResponseCode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getRequest", js_cocos2dx_h_HHttpResponse_getRequest, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getResponseHeader", js_cocos2dx_h_HHttpResponse_getResponseHeader, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getResponseData", js_cocos2dx_h_HHttpResponse_getResponseData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_cocos2d_h_HHttpResponse_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HHttpResponse_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HHttpResponse", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HHttpResponse> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HHttpResponse_class;
		p->proto = jsb_cocos2d_h_HHttpResponse_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HNetwork_class;
JSObject *jsb_cocos2d_h_HNetwork_prototype;

bool js_cocos2dx_h_HNetwork_isInternetConnectionAvailable(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		bool ret = cocos2d::h::HNetwork::isInternetConnectionAvailable();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNetwork_isInternetConnectionAvailable : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNetwork_isLocalWiFiAvailable(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		bool ret = cocos2d::h::HNetwork::isLocalWiFiAvailable();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNetwork_isLocalWiFiAvailable : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNetwork_getInternetConnectionStatus(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		int ret = cocos2d::h::HNetwork::getInternetConnectionStatus();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNetwork_getInternetConnectionStatus : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HNetwork_isHostNameReachable(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HNetwork_isHostNameReachable : Error processing arguments");
		bool ret = cocos2d::h::HNetwork::isHostNameReachable(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HNetwork_isHostNameReachable : wrong number of arguments");
	return false;
}



void js_cocos2d_h_HNetwork_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HNetwork)", obj);
}

void js_register_cocos2dx_h_HNetwork(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HNetwork_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HNetwork_class->name = "HNetwork";
	jsb_cocos2d_h_HNetwork_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HNetwork_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HNetwork_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HNetwork_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HNetwork_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HNetwork_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HNetwork_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HNetwork_class->finalize = js_cocos2d_h_HNetwork_finalize;
	jsb_cocos2d_h_HNetwork_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("isInternetConnectionAvailable", js_cocos2dx_h_HNetwork_isInternetConnectionAvailable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isLocalWiFiAvailable", js_cocos2dx_h_HNetwork_isLocalWiFiAvailable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInternetConnectionStatus", js_cocos2dx_h_HNetwork_getInternetConnectionStatus, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isHostNameReachable", js_cocos2dx_h_HNetwork_isHostNameReachable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HNetwork_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HNetwork_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HNetwork", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HNetwork> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HNetwork_class;
		p->proto = jsb_cocos2d_h_HNetwork_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HSocket_class;
JSObject *jsb_cocos2d_h_HSocket_prototype;



void js_cocos2d_h_HSocket_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HSocket)", obj);
}

void js_register_cocos2dx_h_HSocket(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HSocket_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HSocket_class->name = "HSocket";
	jsb_cocos2d_h_HSocket_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HSocket_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HSocket_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HSocket_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HSocket_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HSocket_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HSocket_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HSocket_class->finalize = js_cocos2d_h_HSocket_finalize;
	jsb_cocos2d_h_HSocket_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_cocos2d_h_HSocket_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HSocket_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HSocket", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HSocket> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HSocket_class;
		p->proto = jsb_cocos2d_h_HSocket_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HSocketManager_class;
JSObject *jsb_cocos2d_h_HSocketManager_prototype;

bool js_cocos2dx_h_HSocketManager_disconnectURL(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HSocketManager* cobj = (cocos2d::h::HSocketManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HSocketManager_disconnectURL : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HSocketManager_disconnectURL : Error processing arguments");
		bool ret = cobj->disconnectURL(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HSocketManager_disconnectURL : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HSocketManager_connectIP(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HSocketManager* cobj = (cocos2d::h::HSocketManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HSocketManager_connectIP : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HSocketManager_connectIP : Error processing arguments");
		cocos2d::h::HSocket* ret = cobj->connectIP(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSocket>(cx, (cocos2d::h::HSocket*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	if (argc == 3) {
		const char* arg0;
		int arg1;
		int arg2;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HSocketManager_connectIP : Error processing arguments");
		cocos2d::h::HSocket* ret = cobj->connectIP(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSocket>(cx, (cocos2d::h::HSocket*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HSocketManager_connectIP : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dx_h_HSocketManager_disconnectIP(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HSocketManager* cobj = (cocos2d::h::HSocketManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HSocketManager_disconnectIP : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HSocketManager_disconnectIP : Error processing arguments");
		bool ret = cobj->disconnectIP(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HSocketManager_disconnectIP : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_cocos2dx_h_HSocketManager_connectURL(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HSocketManager* cobj = (cocos2d::h::HSocketManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HSocketManager_connectURL : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HSocketManager_connectURL : Error processing arguments");
		cocos2d::h::HSocket* ret = cobj->connectURL(arg0);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSocket>(cx, (cocos2d::h::HSocket*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HSocketManager_connectURL : Error processing arguments");
		cocos2d::h::HSocket* ret = cobj->connectURL(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSocket>(cx, (cocos2d::h::HSocket*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HSocketManager_connectURL : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HSocketManager_end(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::h::HSocketManager::end();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HSocketManager_end : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HSocketManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::h::HSocketManager* ret = cocos2d::h::HSocketManager::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSocketManager>(cx, (cocos2d::h::HSocketManager*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HSocketManager_getInstance : wrong number of arguments");
	return false;
}



void js_cocos2d_h_HSocketManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HSocketManager)", obj);
}

void js_register_cocos2dx_h_HSocketManager(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HSocketManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HSocketManager_class->name = "HSocketManager";
	jsb_cocos2d_h_HSocketManager_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HSocketManager_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HSocketManager_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HSocketManager_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HSocketManager_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HSocketManager_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HSocketManager_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HSocketManager_class->finalize = js_cocos2d_h_HSocketManager_finalize;
	jsb_cocos2d_h_HSocketManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("disconnectURL", js_cocos2dx_h_HSocketManager_disconnectURL, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("connectIP", js_cocos2dx_h_HSocketManager_connectIP, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("disconnectIP", js_cocos2dx_h_HSocketManager_disconnectIP, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("connectURL", js_cocos2dx_h_HSocketManager_connectURL, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("end", js_cocos2dx_h_HSocketManager_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInstance", js_cocos2dx_h_HSocketManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HSocketManager_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HSocketManager_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HSocketManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HSocketManager> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HSocketManager_class;
		p->proto = jsb_cocos2d_h_HSocketManager_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HStore_class;
JSObject *jsb_cocos2d_h_HStore_prototype;

bool js_cocos2dx_h_HStore_canMakePurchases(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_canMakePurchases : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->canMakePurchases();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_canMakePurchases : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HStore_cancelLoadProducts(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_cancelLoadProducts : Invalid Native Object");
	if (argc == 0) {
		cobj->cancelLoadProducts();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_cancelLoadProducts : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HStore_setReceiptVerifyMode(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_setReceiptVerifyMode : Invalid Native Object");
	if (argc == 1) {
		cocos2d::h::HStorePaymentTransaction::ReceiptVerifyMode arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HStore_setReceiptVerifyMode : Error processing arguments");
		cobj->setReceiptVerifyMode(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	if (argc == 2) {
		cocos2d::h::HStorePaymentTransaction::ReceiptVerifyMode arg0;
		bool arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		arg1 = JS::ToBoolean(JS::RootedValue(cx, argv[1]));
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HStore_setReceiptVerifyMode : Error processing arguments");
		cobj->setReceiptVerifyMode(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_setReceiptVerifyMode : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HStore_restoreCompletedTransactions(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_restoreCompletedTransactions : Invalid Native Object");
	if (argc == 0) {
		cobj->restoreCompletedTransactions();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_restoreCompletedTransactions : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HStore_purchase(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_purchase : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HStore_purchase : Error processing arguments");
		bool ret = cobj->purchase(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HStore_purchase : Error processing arguments");
		bool ret = cobj->purchase(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_purchase : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HStore_getReceiptVerifyServerUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_getReceiptVerifyServerUrl : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getReceiptVerifyServerUrl();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_getReceiptVerifyServerUrl : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HStore_setUserAccount(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_setUserAccount : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HStore_setUserAccount : Error processing arguments");
		cobj->setUserAccount(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_setUserAccount : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HStore_setReceiptVerifyServerUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_setReceiptVerifyServerUrl : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HStore_setReceiptVerifyServerUrl : Error processing arguments");
		cobj->setReceiptVerifyServerUrl(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_setReceiptVerifyServerUrl : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HStore_isProductLoaded(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_isProductLoaded : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HStore_isProductLoaded : Error processing arguments");
		bool ret = cobj->isProductLoaded(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_isProductLoaded : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HStore_getUserAccount(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_getUserAccount : Invalid Native Object");
	if (argc == 0) {
		const std::string& ret = cobj->getUserAccount();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_getUserAccount : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HStore_finishTransaction(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_finishTransaction : Invalid Native Object");
	if (argc == 1) {
		cocos2d::h::HStorePaymentTransaction* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::h::HStorePaymentTransaction*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HStore_finishTransaction : Error processing arguments");
		cobj->finishTransaction(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_finishTransaction : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HStore_getReceiptVerifyMode(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HStore* cobj = (cocos2d::h::HStore *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HStore_getReceiptVerifyMode : Invalid Native Object");
	if (argc == 0) {
		int ret = (int)cobj->getReceiptVerifyMode();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HStore_getReceiptVerifyMode : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HStore_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::h::HStore::destroyInstance();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HStore_destroyInstance : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HStore_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::h::HStore* ret = cocos2d::h::HStore::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HStore>(cx, (cocos2d::h::HStore*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HStore_getInstance : wrong number of arguments");
	return false;
}



void js_cocos2d_h_HStore_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HStore)", obj);
}

void js_register_cocos2dx_h_HStore(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HStore_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HStore_class->name = "HStore";
	jsb_cocos2d_h_HStore_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HStore_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HStore_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HStore_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HStore_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HStore_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HStore_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HStore_class->finalize = js_cocos2d_h_HStore_finalize;
	jsb_cocos2d_h_HStore_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("canMakePurchases", js_cocos2dx_h_HStore_canMakePurchases, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("cancelLoadProducts", js_cocos2dx_h_HStore_cancelLoadProducts, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setReceiptVerifyMode", js_cocos2dx_h_HStore_setReceiptVerifyMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("restoreCompletedTransactions", js_cocos2dx_h_HStore_restoreCompletedTransactions, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("purchase", js_cocos2dx_h_HStore_purchase, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getReceiptVerifyServerUrl", js_cocos2dx_h_HStore_getReceiptVerifyServerUrl, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setUserAccount", js_cocos2dx_h_HStore_setUserAccount, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setReceiptVerifyServerUrl", js_cocos2dx_h_HStore_setReceiptVerifyServerUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isProductLoaded", js_cocos2dx_h_HStore_isProductLoaded, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getUserAccount", js_cocos2dx_h_HStore_getUserAccount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("finishTransaction", js_cocos2dx_h_HStore_finishTransaction, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getReceiptVerifyMode", js_cocos2dx_h_HStore_getReceiptVerifyMode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("destroyInstance", js_cocos2dx_h_HStore_destroyInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInstance", js_cocos2dx_h_HStore_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HStore_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HStore_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HStore", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HStore> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HStore_class;
		p->proto = jsb_cocos2d_h_HStore_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HLogFile_class;
JSObject *jsb_cocos2d_h_HLogFile_prototype;

bool js_cocos2dx_h_HLogFile_getDefaultLogFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		std::string ret = cocos2d::h::HLogFile::getDefaultLogFile();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HLogFile_getDefaultLogFile : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HLogFile_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 0) {
		cocos2d::h::HLogFile::clear();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HLogFile_clear : Error processing arguments");
		cocos2d::h::HLogFile::clear(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HLogFile_clear : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HLogFile_logFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HLogFile_logFile : Error processing arguments");
		cocos2d::h::HLogFile::logFile(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	if (argc == 2) {
		const char* arg0;
		const char* arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HLogFile_logFile : Error processing arguments");
		cocos2d::h::HLogFile::logFile(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HLogFile_logFile : wrong number of arguments");
	return false;
}



void js_cocos2d_h_HLogFile_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HLogFile)", obj);
}

void js_register_cocos2dx_h_HLogFile(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HLogFile_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HLogFile_class->name = "HLogFile";
	jsb_cocos2d_h_HLogFile_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HLogFile_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HLogFile_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HLogFile_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HLogFile_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HLogFile_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HLogFile_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HLogFile_class->finalize = js_cocos2d_h_HLogFile_finalize;
	jsb_cocos2d_h_HLogFile_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("getDefaultLogFile", js_cocos2dx_h_HLogFile_getDefaultLogFile, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("clear", js_cocos2dx_h_HLogFile_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logFile", js_cocos2dx_h_HLogFile_logFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HLogFile_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HLogFile_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HLogFile", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HLogFile> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HLogFile_class;
		p->proto = jsb_cocos2d_h_HLogFile_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HShaderCustom_class;
JSObject *jsb_cocos2d_h_HShaderCustom_prototype;

bool js_cocos2dx_h_HShaderCustom_createGray(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 0) {
		cocos2d::GLProgram* ret = cocos2d::h::HShaderCustom::createGray();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::GLProgram>(cx, (cocos2d::GLProgram*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	if (argc == 1) {
		bool arg0;
		arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HShaderCustom_createGray : Error processing arguments");
		cocos2d::GLProgram* ret = cocos2d::h::HShaderCustom::createGray(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::GLProgram>(cx, (cocos2d::GLProgram*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HShaderCustom_createGray : wrong number of arguments");
	return false;
}



void js_cocos2d_h_HShaderCustom_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HShaderCustom)", obj);
}

void js_register_cocos2dx_h_HShaderCustom(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HShaderCustom_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HShaderCustom_class->name = "HShaderCustom";
	jsb_cocos2d_h_HShaderCustom_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HShaderCustom_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HShaderCustom_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HShaderCustom_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HShaderCustom_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HShaderCustom_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HShaderCustom_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HShaderCustom_class->finalize = js_cocos2d_h_HShaderCustom_finalize;
	jsb_cocos2d_h_HShaderCustom_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("createGray", js_cocos2dx_h_HShaderCustom_createGray, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HShaderCustom_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_HShaderCustom_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HShaderCustom", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HShaderCustom> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HShaderCustom_class;
		p->proto = jsb_cocos2d_h_HShaderCustom_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HActionBlurFromTo_class;
JSObject *jsb_cocos2d_h_HActionBlurFromTo_prototype;

bool js_cocos2dx_h_HActionBlurFromTo_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HActionBlurFromTo* cobj = (cocos2d::h::HActionBlurFromTo *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HActionBlurFromTo_initWithDuration : Invalid Native Object");
	if (argc == 3) {
		double arg0;
		double arg1;
		double arg2;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[1]), &arg1);
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[2]), &arg2);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HActionBlurFromTo_initWithDuration : Error processing arguments");
		bool ret = cobj->initWithDuration(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HActionBlurFromTo_initWithDuration : wrong number of arguments: %d, was expecting %d", argc, 3);
	return false;
}
bool js_cocos2dx_h_HActionBlurFromTo_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 3) {
		double arg0;
		double arg1;
		double arg2;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[1]), &arg1);
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[2]), &arg2);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HActionBlurFromTo_create : Error processing arguments");
		cocos2d::h::HActionBlurFromTo* ret = cocos2d::h::HActionBlurFromTo::create(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HActionBlurFromTo>(cx, (cocos2d::h::HActionBlurFromTo*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HActionBlurFromTo_create : wrong number of arguments");
	return false;
}


extern JSObject *jsb_cocos2d_ActionInterval_prototype;

void js_cocos2d_h_HActionBlurFromTo_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HActionBlurFromTo)", obj);
}

void js_register_cocos2dx_h_HActionBlurFromTo(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HActionBlurFromTo_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HActionBlurFromTo_class->name = "HActionBlurFromTo";
	jsb_cocos2d_h_HActionBlurFromTo_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HActionBlurFromTo_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HActionBlurFromTo_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HActionBlurFromTo_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HActionBlurFromTo_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HActionBlurFromTo_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HActionBlurFromTo_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HActionBlurFromTo_class->finalize = js_cocos2d_h_HActionBlurFromTo_finalize;
	jsb_cocos2d_h_HActionBlurFromTo_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("initWithDuration", js_cocos2dx_h_HActionBlurFromTo_initWithDuration, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_h_HActionBlurFromTo_create, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HActionBlurFromTo_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_ActionInterval_prototype,
		jsb_cocos2d_h_HActionBlurFromTo_class,
		dummy_constructor<cocos2d::h::HActionBlurFromTo>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HActionBlurFromTo", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HActionBlurFromTo> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HActionBlurFromTo_class;
		p->proto = jsb_cocos2d_h_HActionBlurFromTo_prototype;
		p->parentProto = jsb_cocos2d_ActionInterval_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HScale9Sprite_class;
JSObject *jsb_cocos2d_h_HScale9Sprite_prototype;

bool js_cocos2dx_h_HScale9Sprite_getScale9Image(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HScale9Sprite* cobj = (cocos2d::h::HScale9Sprite *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HScale9Sprite_getScale9Image : Invalid Native Object");
	if (argc == 0) {
		cocos2d::SpriteBatchNode* ret = cobj->getScale9Image();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::SpriteBatchNode>(cx, (cocos2d::SpriteBatchNode*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HScale9Sprite_getScale9Image : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HScale9Sprite_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	
	do {
		if (argc == 3) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= jsval_to_ccrect(cx, argv[1], &arg1);
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg2;
			ok &= jsval_to_ccrect(cx, argv[2], &arg2);
			if (!ok) { ok = true; break; }
			cocos2d::h::HScale9Sprite* ret = cocos2d::h::HScale9Sprite::create(arg0, arg1, arg2);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HScale9Sprite>(cx, (cocos2d::h::HScale9Sprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 0) {
			cocos2d::h::HScale9Sprite* ret = cocos2d::h::HScale9Sprite::create();
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HScale9Sprite>(cx, (cocos2d::h::HScale9Sprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 2) {
			cocos2d::Rect arg0;
			ok &= jsval_to_ccrect(cx, argv[0], &arg0);
			if (!ok) { ok = true; break; }
			const char* arg1;
			std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::h::HScale9Sprite* ret = cocos2d::h::HScale9Sprite::create(arg0, arg1);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HScale9Sprite>(cx, (cocos2d::h::HScale9Sprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= jsval_to_ccrect(cx, argv[1], &arg1);
			if (!ok) { ok = true; break; }
			cocos2d::h::HScale9Sprite* ret = cocos2d::h::HScale9Sprite::create(arg0, arg1);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HScale9Sprite>(cx, (cocos2d::h::HScale9Sprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::h::HScale9Sprite* ret = cocos2d::h::HScale9Sprite::create(arg0);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HScale9Sprite>(cx, (cocos2d::h::HScale9Sprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	JS_ReportError(cx, "js_cocos2dx_h_HScale9Sprite_create : wrong number of arguments");
	return false;
}
bool js_cocos2dx_h_HScale9Sprite_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	
	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= jsval_to_ccrect(cx, argv[1], &arg1);
			if (!ok) { ok = true; break; }
			cocos2d::h::HScale9Sprite* ret = cocos2d::h::HScale9Sprite::createWithSpriteFrameName(arg0, arg1);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HScale9Sprite>(cx, (cocos2d::h::HScale9Sprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::h::HScale9Sprite* ret = cocos2d::h::HScale9Sprite::createWithSpriteFrameName(arg0);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HScale9Sprite>(cx, (cocos2d::h::HScale9Sprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	JS_ReportError(cx, "js_cocos2dx_h_HScale9Sprite_createWithSpriteFrameName : wrong number of arguments");
	return false;
}
bool js_cocos2dx_h_HScale9Sprite_createWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	
	do {
		if (argc == 2) {
			cocos2d::SpriteFrame* arg0;
			do {
				if (!argv[0].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= jsval_to_ccrect(cx, argv[1], &arg1);
			if (!ok) { ok = true; break; }
			cocos2d::h::HScale9Sprite* ret = cocos2d::h::HScale9Sprite::createWithSpriteFrame(arg0, arg1);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HScale9Sprite>(cx, (cocos2d::h::HScale9Sprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 1) {
			cocos2d::SpriteFrame* arg0;
			do {
				if (!argv[0].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cocos2d::h::HScale9Sprite* ret = cocos2d::h::HScale9Sprite::createWithSpriteFrame(arg0);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HScale9Sprite>(cx, (cocos2d::h::HScale9Sprite*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	JS_ReportError(cx, "js_cocos2dx_h_HScale9Sprite_createWithSpriteFrame : wrong number of arguments");
	return false;
}

extern JSObject *jsb_cocos2d_extension_Scale9Sprite_prototype;

void js_cocos2d_h_HScale9Sprite_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HScale9Sprite)", obj);
}

void js_register_cocos2dx_h_HScale9Sprite(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HScale9Sprite_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HScale9Sprite_class->name = "HScale9Sprite";
	jsb_cocos2d_h_HScale9Sprite_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HScale9Sprite_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HScale9Sprite_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HScale9Sprite_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HScale9Sprite_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HScale9Sprite_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HScale9Sprite_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HScale9Sprite_class->finalize = js_cocos2d_h_HScale9Sprite_finalize;
	jsb_cocos2d_h_HScale9Sprite_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getScale9Image", js_cocos2dx_h_HScale9Sprite_getScale9Image, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_h_HScale9Sprite_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithSpriteFrameName", js_cocos2dx_h_HScale9Sprite_createWithSpriteFrameName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithSpriteFrame", js_cocos2dx_h_HScale9Sprite_createWithSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HScale9Sprite_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_extension_Scale9Sprite_prototype,
		jsb_cocos2d_h_HScale9Sprite_class,
		dummy_constructor<cocos2d::h::HScale9Sprite>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HScale9Sprite", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HScale9Sprite> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HScale9Sprite_class;
		p->proto = jsb_cocos2d_h_HScale9Sprite_prototype;
		p->parentProto = jsb_cocos2d_extension_Scale9Sprite_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HSpriteBlur_class;
JSObject *jsb_cocos2d_h_HSpriteBlur_prototype;

bool js_cocos2dx_h_HSpriteBlur_setBlurSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HSpriteBlur* cobj = (cocos2d::h::HSpriteBlur *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HSpriteBlur_setBlurSize : Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HSpriteBlur_setBlurSize : Error processing arguments");
		cobj->setBlurSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HSpriteBlur_setBlurSize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HSpriteBlur_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::h::HSpriteBlur* ret = cocos2d::h::HSpriteBlur::create(arg0);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSpriteBlur>(cx, (cocos2d::h::HSpriteBlur*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 0) {
			cocos2d::h::HSpriteBlur* ret = cocos2d::h::HSpriteBlur::create();
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSpriteBlur>(cx, (cocos2d::h::HSpriteBlur*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= jsval_to_ccrect(cx, argv[1], &arg1);
			if (!ok) { ok = true; break; }
			cocos2d::h::HSpriteBlur* ret = cocos2d::h::HSpriteBlur::create(arg0, arg1);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSpriteBlur>(cx, (cocos2d::h::HSpriteBlur*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	JS_ReportError(cx, "js_cocos2dx_h_HSpriteBlur_create : wrong number of arguments");
	return false;
}
bool js_cocos2dx_h_HSpriteBlur_createWithTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	
	do {
		if (argc == 2) {
			cocos2d::Texture2D* arg0;
			do {
				if (!argv[0].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg0 = (cocos2d::Texture2D*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cocos2d::Rect arg1;
			ok &= jsval_to_ccrect(cx, argv[1], &arg1);
			if (!ok) { ok = true; break; }
			cocos2d::h::HSpriteBlur* ret = cocos2d::h::HSpriteBlur::createWithTexture(arg0, arg1);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSpriteBlur>(cx, (cocos2d::h::HSpriteBlur*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	
	do {
		if (argc == 1) {
			cocos2d::Texture2D* arg0;
			do {
				if (!argv[0].isObject()) { ok = false; break; }
				js_proxy_t *jsProxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				jsProxy = jsb_get_js_proxy(tmpObj);
				arg0 = (cocos2d::Texture2D*)(jsProxy ? jsProxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = true; break; }
			cocos2d::h::HSpriteBlur* ret = cocos2d::h::HSpriteBlur::createWithTexture(arg0);
			jsval jsret = JSVAL_NULL;
			do {
				if (ret) {
					js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSpriteBlur>(cx, (cocos2d::h::HSpriteBlur*)ret);
					jsret = OBJECT_TO_JSVAL(jsProxy->obj);
				} else {
					jsret = JSVAL_NULL;
				}
			} while (0);
			JS_SET_RVAL(cx, vp, jsret);
			return true;
		}
	} while (0);
	JS_ReportError(cx, "js_cocos2dx_h_HSpriteBlur_createWithTexture : wrong number of arguments");
	return false;
}
bool js_cocos2dx_h_HSpriteBlur_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HSpriteBlur_createWithSpriteFrameName : Error processing arguments");
		cocos2d::h::HSpriteBlur* ret = cocos2d::h::HSpriteBlur::createWithSpriteFrameName(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSpriteBlur>(cx, (cocos2d::h::HSpriteBlur*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HSpriteBlur_createWithSpriteFrameName : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HSpriteBlur_createWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::SpriteFrame* arg0;
		do {
			if (!argv[0].isObject()) { ok = false; break; }
			js_proxy_t *jsProxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			jsProxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HSpriteBlur_createWithSpriteFrame : Error processing arguments");
		cocos2d::h::HSpriteBlur* ret = cocos2d::h::HSpriteBlur::createWithSpriteFrame(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HSpriteBlur>(cx, (cocos2d::h::HSpriteBlur*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HSpriteBlur_createWithSpriteFrame : wrong number of arguments");
	return false;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_cocos2d_h_HSpriteBlur_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HSpriteBlur)", obj);
}

void js_register_cocos2dx_h_HSpriteBlur(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HSpriteBlur_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HSpriteBlur_class->name = "HSpriteBlur";
	jsb_cocos2d_h_HSpriteBlur_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HSpriteBlur_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HSpriteBlur_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HSpriteBlur_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HSpriteBlur_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HSpriteBlur_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HSpriteBlur_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HSpriteBlur_class->finalize = js_cocos2d_h_HSpriteBlur_finalize;
	jsb_cocos2d_h_HSpriteBlur_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("setBlurSize", js_cocos2dx_h_HSpriteBlur_setBlurSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_h_HSpriteBlur_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithTexture", js_cocos2dx_h_HSpriteBlur_createWithTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithSpriteFrameName", js_cocos2dx_h_HSpriteBlur_createWithSpriteFrameName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createWithSpriteFrame", js_cocos2dx_h_HSpriteBlur_createWithSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HSpriteBlur_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_Sprite_prototype,
		jsb_cocos2d_h_HSpriteBlur_class,
		dummy_constructor<cocos2d::h::HSpriteBlur>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HSpriteBlur", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HSpriteBlur> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HSpriteBlur_class;
		p->proto = jsb_cocos2d_h_HSpriteBlur_prototype;
		p->parentProto = jsb_cocos2d_Sprite_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_h_HWebView_class;
JSObject *jsb_cocos2d_h_HWebView_prototype;

bool js_cocos2dx_h_HWebView_loadURL(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_loadURL : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HWebView_loadURL : Error processing arguments");
		cobj->loadURL(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_loadURL : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HWebView_setAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_setAnchorPoint : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HWebView_setAnchorPoint : Error processing arguments");
		cobj->setAnchorPoint(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_setAnchorPoint : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HWebView_goForward(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_goForward : Invalid Native Object");
	if (argc == 0) {
		cobj->goForward();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_goForward : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HWebView_goBack(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_goBack : Invalid Native Object");
	if (argc == 0) {
		cobj->goBack();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_goBack : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HWebView_stopLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_stopLoading : Invalid Native Object");
	if (argc == 0) {
		cobj->stopLoading();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_stopLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HWebView_canGoBack(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_canGoBack : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->canGoBack();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_canGoBack : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HWebView_reload(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_reload : Invalid Native Object");
	if (argc == 0) {
		cobj->reload();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_reload : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HWebView_canGoForward(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_canGoForward : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->canGoForward();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_canGoForward : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HWebView_isLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_isLoading : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isLoading();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_isLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2dx_h_HWebView_initWithSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_initWithSize : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HWebView_initWithSize : Error processing arguments");
		bool ret = cobj->initWithSize(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_initWithSize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HWebView_setPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_setPosition : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Point arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HWebView_setPosition : Error processing arguments");
		cobj->setPosition(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_setPosition : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HWebView_setVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_setVisible : Invalid Native Object");
	if (argc == 1) {
		bool arg0;
		arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HWebView_setVisible : Error processing arguments");
		cobj->setVisible(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_setVisible : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HWebView_setContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HWebView* cobj = (cocos2d::h::HWebView *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_h_HWebView_setContentSize : Invalid Native Object");
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HWebView_setContentSize : Error processing arguments");
		cobj->setContentSize(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2dx_h_HWebView_setContentSize : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2dx_h_HWebView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		cocos2d::Size arg0;
		ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_h_HWebView_create : Error processing arguments");
		cocos2d::h::HWebView* ret = cocos2d::h::HWebView::create(arg0);
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::h::HWebView>(cx, (cocos2d::h::HWebView*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2dx_h_HWebView_create : wrong number of arguments");
	return false;
}

bool js_cocos2dx_h_HWebView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
    cocos2d::h::HWebView* cobj = new cocos2d::h::HWebView();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::h::HWebView> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::h::HWebView");
    if (JS_HasProperty(cx, obj, "_ctor", &ok))
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_cocos2d_h_HWebView_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HWebView)", obj);
}

void js_register_cocos2dx_h_HWebView(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_HWebView_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_HWebView_class->name = "HWebView";
	jsb_cocos2d_h_HWebView_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_HWebView_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_HWebView_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_HWebView_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_HWebView_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_HWebView_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_HWebView_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_HWebView_class->finalize = js_cocos2d_h_HWebView_finalize;
	jsb_cocos2d_h_HWebView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("loadURL", js_cocos2dx_h_HWebView_loadURL, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setAnchorPoint", js_cocos2dx_h_HWebView_setAnchorPoint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("goForward", js_cocos2dx_h_HWebView_goForward, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("goBack", js_cocos2dx_h_HWebView_goBack, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("stopLoading", js_cocos2dx_h_HWebView_stopLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("canGoBack", js_cocos2dx_h_HWebView_canGoBack, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("reload", js_cocos2dx_h_HWebView_reload, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("canGoForward", js_cocos2dx_h_HWebView_canGoForward, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isLoading", js_cocos2dx_h_HWebView_isLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("initWithSize", js_cocos2dx_h_HWebView_initWithSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPosition", js_cocos2dx_h_HWebView_setPosition, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setVisible", js_cocos2dx_h_HWebView_setVisible, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setContentSize", js_cocos2dx_h_HWebView_setContentSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_h_HWebView_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HWebView_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_Node_prototype,
		jsb_cocos2d_h_HWebView_class,
		js_cocos2dx_h_HWebView_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "HWebView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::HWebView> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_HWebView_class;
		p->proto = jsb_cocos2d_h_HWebView_prototype;
		p->parentProto = jsb_cocos2d_Node_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

void register_all_cocos2dx_h(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	JS::RootedValue nsval(cx);
	JS::RootedObject ns(cx);
	JS_GetProperty(cx, obj, "cch", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "cch", nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_cocos2dx_h_HNative(cx, obj);
	js_register_cocos2dx_h_HBFPacket(cx, obj);
	js_register_cocos2dx_h_HScale9Sprite(cx, obj);
	js_register_cocos2dx_h_HAssetsManager(cx, obj);
	js_register_cocos2dx_h_HActionBlurFromTo(cx, obj);
	js_register_cocos2dx_h_HHttpPacker(cx, obj);
	js_register_cocos2dx_h_HNetwork(cx, obj);
	js_register_cocos2dx_h_HStore(cx, obj);
	js_register_cocos2dx_h_HSocket(cx, obj);
	js_register_cocos2dx_h_HShaderCustom(cx, obj);
	js_register_cocos2dx_h_HLogFile(cx, obj);
	js_register_cocos2dx_h_HHttpRequest(cx, obj);
	js_register_cocos2dx_h_HSpriteBlur(cx, obj);
	js_register_cocos2dx_h_HWebView(cx, obj);
	js_register_cocos2dx_h_HHttpResponse(cx, obj);
	js_register_cocos2dx_h_HSocketManager(cx, obj);
	js_register_cocos2dx_h_HMSPacket(cx, obj);
}

