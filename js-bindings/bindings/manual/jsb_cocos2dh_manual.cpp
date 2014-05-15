/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   资源管理
 @History       (操作 -- 创建)(时间 -- 13-3-6)
 */

#include "jsb_cocos2dh_manual.h"
#include "ScriptingCore.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#endif

USING_NS_CC;

static bool js_cch_restartVM(JSContext *cx, uint32_t argc, jsval *vp)
{
    auto node = Node::create();
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->schedule([=](float){
        scheduler->unscheduleAllForTarget(node);
        ScriptingCore::getInstance()->reset();
        ScriptingCore::getInstance()->runScript("main.js");
    }, node, 0, false, "restartVM");
    return false;
}

static bool __mkdir(const char *path) {
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    mode_t processMask = umask(0);
    int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
    umask(processMask);
    if (ret != 0 && (errno != EEXIST))
    {
        return false;
    }
    
    return true;
#else
    BOOL ret = CreateDirectoryA(path, NULL);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
    return true;
#endif
}

static bool js_cch_mkdir(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2(argc == 1, cx, false, "Invalid number of arguments");
	jsval *argv = JS_ARGV(cx,vp);
	bool ok = true;
	std::string arg0;
    
	ok &= jsval_to_std_string(cx, *argv++, &arg0);
	JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
    
	jsval jsret = BOOLEAN_TO_JSVAL(__mkdir(arg0.c_str()));

    JS_SET_RVAL(cx, vp, jsret);
	return true;
}

void __rmdir(const char *path) {
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    std::string command = "rm -r ";
    // Path may include space.
    command += "\"";
    command += path;
    command += "\"";
    system(command.c_str());
#else
    string command = "rd /s /q ";
    // Path may include space.
    command += "\"";
    command += path;
    command += "\"";
    system(command.c_str());
#endif
}

static bool js_cch_rmdir(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2(argc == 1, cx, false, "Invalid number of arguments");
	jsval *argv = JS_ARGV(cx,vp);
	bool ok = true;
	std::string arg0;
    
	ok &= jsval_to_std_string(cx, *argv++, &arg0);
	JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
    
    __rmdir(arg0.c_str());
    
    JS_SET_RVAL(cx, vp, JSVAL_NULL);
	return true;
}

void register_all_cocos2dh_manual(JSContext* cx, JSObject* obj) {
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
    
	JS_DefineFunction(cx, ns, "restartVM", js_cch_restartVM, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "mkdir", js_cch_mkdir, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "rmdir", js_cch_rmdir, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}
