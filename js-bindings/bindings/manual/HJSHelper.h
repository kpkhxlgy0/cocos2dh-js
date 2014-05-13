#ifndef __BINDINGSJS_HJSHELPER_H__
#define __BINDINGSJS_HJSHELPER_H__

#include "jsapi.h"
#include "jsfriendapi.h"

#define HJSHELPER_DEFINEFUNC_INIT(name) \
JS::RootedValue nsval(cx);\
JS::RootedObject ns(cx);\
JS_GetProperty(cx, global, name, &nsval);\
if (nsval == JSVAL_VOID) {\
    ns = JS_NewObject(cx, NULL, NULL, NULL);\
    nsval = OBJECT_TO_JSVAL(ns);\
    JS_SetProperty(cx, global, name, nsval);\
} else {\
    JS_ValueToObject(cx, nsval, &ns);\
}\
global = ns;

namespace js {
extern JS_PUBLIC_API(bool)
    IsInRequest(JSContext *cx);
}

void register_HJSHelper(JSContext *cx, JSObject *global);

#endif // __BINDINGSJS_HJSHELPER_H__
