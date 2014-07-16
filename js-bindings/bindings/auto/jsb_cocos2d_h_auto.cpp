#include "jsb_cocos2d_h_auto.hpp"
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
JSClass  *jsb_cocos2d_h_HAssetsManager_class;
JSObject *jsb_cocos2d_h_HAssetsManager_prototype;

bool js_cocos2d_h_HAssetsManager_setStoragePath(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_setStoragePath : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_HAssetsManager_setStoragePath : Error processing arguments");
		cobj->setStoragePath(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_setStoragePath : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2d_h_HAssetsManager_setPackageUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_setPackageUrl : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_HAssetsManager_setPackageUrl : Error processing arguments");
		cobj->setPackageUrl(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_setPackageUrl : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2d_h_HAssetsManager_checkUpdate(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_checkUpdate : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->checkUpdate();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_checkUpdate : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2d_h_HAssetsManager_getStoragePath(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_getStoragePath : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getStoragePath();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_getStoragePath : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2d_h_HAssetsManager_update(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_update : Invalid Native Object");
	if (argc == 0) {
		cobj->update();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_update : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2d_h_HAssetsManager_setConnectionTimeout(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_setConnectionTimeout : Invalid Native Object");
	if (argc == 1) {
		unsigned int arg0;
		ok &= jsval_to_uint32(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_HAssetsManager_setConnectionTimeout : Error processing arguments");
		cobj->setConnectionTimeout(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_setConnectionTimeout : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2d_h_HAssetsManager_setVersionFileUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_setVersionFileUrl : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_HAssetsManager_setVersionFileUrl : Error processing arguments");
		cobj->setVersionFileUrl(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_setVersionFileUrl : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_cocos2d_h_HAssetsManager_getPackageUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_getPackageUrl : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getPackageUrl();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_getPackageUrl : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2d_h_HAssetsManager_getConnectionTimeout(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_getConnectionTimeout : Invalid Native Object");
	if (argc == 0) {
		unsigned int ret = cobj->getConnectionTimeout();
		jsval jsret = JSVAL_NULL;
		jsret = uint32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_getConnectionTimeout : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2d_h_HAssetsManager_getVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_getVersion : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getVersion();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_getVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2d_h_HAssetsManager_getVersionFileUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_getVersionFileUrl : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getVersionFileUrl();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_getVersionFileUrl : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2d_h_HAssetsManager_deleteVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::h::HAssetsManager* cobj = (cocos2d::h::HAssetsManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_cocos2d_h_HAssetsManager_deleteVersion : Invalid Native Object");
	if (argc == 0) {
		cobj->deleteVersion();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_deleteVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_cocos2d_h_HAssetsManager_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 6) {
		const char* arg0;
		const char* arg1;
		const char* arg2;
		std::function<void (int)> arg3;
		std::function<void (int)> arg4;
		std::function<void ()> arg5;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
		do {
			std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[3]));
			auto lambda = [=](int larg0) -> void {
				jsval largv[1];
				largv[0] = int32_to_jsval(cx, larg0);
				jsval rval;
				bool ok = func->invoke(1, &largv[0], rval);
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
			auto lambda = [=]() -> void {
				jsval rval;
				bool ok = func->invoke(0, nullptr, rval);
				if (!ok && JS_IsExceptionPending(cx)) {
					JS_ReportPendingException(cx);
				}
			};
			arg5 = lambda;
		} while(0)
		;
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_HAssetsManager_create : Error processing arguments");
		cocos2d::h::HAssetsManager* ret = cocos2d::h::HAssetsManager::create(arg0, arg1, arg2, arg3, arg4, arg5);
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
	JS_ReportError(cx, "js_cocos2d_h_HAssetsManager_create : wrong number of arguments");
	return false;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_cocos2d_h_HAssetsManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HAssetsManager)", obj);
}

void js_register_cocos2d_h_HAssetsManager(JSContext *cx, JSObject *global) {
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
		JS_FN("setStoragePath", js_cocos2d_h_HAssetsManager_setStoragePath, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPackageUrl", js_cocos2d_h_HAssetsManager_setPackageUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("checkUpdate", js_cocos2d_h_HAssetsManager_checkUpdate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStoragePath", js_cocos2d_h_HAssetsManager_getStoragePath, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("update", js_cocos2d_h_HAssetsManager_update, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setConnectionTimeout", js_cocos2d_h_HAssetsManager_setConnectionTimeout, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setVersionFileUrl", js_cocos2d_h_HAssetsManager_setVersionFileUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPackageUrl", js_cocos2d_h_HAssetsManager_getPackageUrl, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getConnectionTimeout", js_cocos2d_h_HAssetsManager_getConnectionTimeout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getVersion", js_cocos2d_h_HAssetsManager_getVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getVersionFileUrl", js_cocos2d_h_HAssetsManager_getVersionFileUrl, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("deleteVersion", js_cocos2d_h_HAssetsManager_deleteVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2d_h_HAssetsManager_create, 6, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_HAssetsManager_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_Node_prototype,
		jsb_cocos2d_h_HAssetsManager_class,
		empty_constructor, 0,
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

JSClass  *jsb_cocos2d_h_AssetsManagerExt_class;
JSObject *jsb_cocos2d_h_AssetsManagerExt_prototype;

bool js_cocos2d_h_AssetsManagerExt_changeExt(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 2) {
		std::string arg0;
		std::string arg1;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_changeExt : Error processing arguments");
		std::string ret = cocos2d::h::AssetsManagerExt::changeExt(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2d_h_AssetsManagerExt_changeExt : wrong number of arguments");
	return false;
}

bool js_cocos2d_h_AssetsManagerExt_removeDirectory(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_removeDirectory : Error processing arguments");
		bool ret = cocos2d::h::AssetsManagerExt::removeDirectory(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2d_h_AssetsManagerExt_removeDirectory : wrong number of arguments");
	return false;
}

bool js_cocos2d_h_AssetsManagerExt_getFileSize(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_getFileSize : Error processing arguments");
		long ret = cocos2d::h::AssetsManagerExt::getFileSize(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = long_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2d_h_AssetsManagerExt_getFileSize : wrong number of arguments");
	return false;
}

bool js_cocos2d_h_AssetsManagerExt_readdir(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_readdir : Error processing arguments");
		std::vector<std::string> ret = cocos2d::h::AssetsManagerExt::readdir(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = std_vector_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	if (argc == 2) {
		std::string arg0;
		bool arg1;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		arg1 = JS::ToBoolean(JS::RootedValue(cx, argv[1]));
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_readdir : Error processing arguments");
		std::vector<std::string> ret = cocos2d::h::AssetsManagerExt::readdir(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = std_vector_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2d_h_AssetsManagerExt_readdir : wrong number of arguments");
	return false;
}

bool js_cocos2d_h_AssetsManagerExt_extname(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_extname : Error processing arguments");
		std::string ret = cocos2d::h::AssetsManagerExt::extname(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2d_h_AssetsManagerExt_extname : wrong number of arguments");
	return false;
}

bool js_cocos2d_h_AssetsManagerExt_removeFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_removeFile : Error processing arguments");
		bool ret = cocos2d::h::AssetsManagerExt::removeFile(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2d_h_AssetsManagerExt_removeFile : wrong number of arguments");
	return false;
}

bool js_cocos2d_h_AssetsManagerExt_isDirectory(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_isDirectory : Error processing arguments");
		bool ret = cocos2d::h::AssetsManagerExt::isDirectory(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2d_h_AssetsManagerExt_isDirectory : wrong number of arguments");
	return false;
}

bool js_cocos2d_h_AssetsManagerExt_renameFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 3) {
		std::string arg0;
		std::string arg1;
		std::string arg2;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		ok &= jsval_to_std_string(cx, argv[2], &arg2);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_renameFile : Error processing arguments");
		bool ret = cocos2d::h::AssetsManagerExt::renameFile(arg0, arg1, arg2);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2d_h_AssetsManagerExt_renameFile : wrong number of arguments");
	return false;
}

bool js_cocos2d_h_AssetsManagerExt_createDirectory(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_createDirectory : Error processing arguments");
		bool ret = cocos2d::h::AssetsManagerExt::createDirectory(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2d_h_AssetsManagerExt_createDirectory : wrong number of arguments");
	return false;
}

bool js_cocos2d_h_AssetsManagerExt_dirname(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_dirname : Error processing arguments");
		std::string ret = cocos2d::h::AssetsManagerExt::dirname(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2d_h_AssetsManagerExt_dirname : wrong number of arguments");
	return false;
}

bool js_cocos2d_h_AssetsManagerExt_basename(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_basename : Error processing arguments");
		std::string ret = cocos2d::h::AssetsManagerExt::basename(arg0);
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
		JSB_PRECONDITION2(ok, cx, false, "js_cocos2d_h_AssetsManagerExt_basename : Error processing arguments");
		std::string ret = cocos2d::h::AssetsManagerExt::basename(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_cocos2d_h_AssetsManagerExt_basename : wrong number of arguments");
	return false;
}



void js_cocos2d_h_AssetsManagerExt_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (AssetsManagerExt)", obj);
}

void js_register_cocos2d_h_AssetsManagerExt(JSContext *cx, JSObject *global) {
	jsb_cocos2d_h_AssetsManagerExt_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_h_AssetsManagerExt_class->name = "AssetsManagerExt";
	jsb_cocos2d_h_AssetsManagerExt_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_h_AssetsManagerExt_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_h_AssetsManagerExt_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_h_AssetsManagerExt_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_h_AssetsManagerExt_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_h_AssetsManagerExt_class->resolve = JS_ResolveStub;
	jsb_cocos2d_h_AssetsManagerExt_class->convert = JS_ConvertStub;
	jsb_cocos2d_h_AssetsManagerExt_class->finalize = js_cocos2d_h_AssetsManagerExt_finalize;
	jsb_cocos2d_h_AssetsManagerExt_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("changeExt", js_cocos2d_h_AssetsManagerExt_changeExt, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeDirectory", js_cocos2d_h_AssetsManagerExt_removeDirectory, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getFileSize", js_cocos2d_h_AssetsManagerExt_getFileSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("readdir", js_cocos2d_h_AssetsManagerExt_readdir, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("extname", js_cocos2d_h_AssetsManagerExt_extname, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeFile", js_cocos2d_h_AssetsManagerExt_removeFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isDirectory", js_cocos2d_h_AssetsManagerExt_isDirectory, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("renameFile", js_cocos2d_h_AssetsManagerExt_renameFile, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("createDirectory", js_cocos2d_h_AssetsManagerExt_createDirectory, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("dirname", js_cocos2d_h_AssetsManagerExt_dirname, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("basename", js_cocos2d_h_AssetsManagerExt_basename, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_h_AssetsManagerExt_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_h_AssetsManagerExt_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "AssetsManagerExt", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::h::AssetsManagerExt> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_h_AssetsManagerExt_class;
		p->proto = jsb_cocos2d_h_AssetsManagerExt_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

void register_all_cocos2d_h(JSContext* cx, JSObject* obj) {
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

	js_register_cocos2d_h_AssetsManagerExt(cx, obj);
	js_register_cocos2d_h_HAssetsManager(cx, obj);
}

