/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   资源管理
 @History       (操作 -- 创建)(时间 -- 13-3-6)
 */

#include "jsb_cocos2dh_manual.h"
#include "ScriptingCore.h"
#include "cocos2d.h"

#include "msgpack.hpp"
#include "json/document.h"

USING_NS_CC;

#pragma mark - modu app

void msgpack2js(std::string &ret, const msgpack::object o, bool asKey = false) {
    if (asKey && o.type != msgpack::type::RAW) {
        ret += "\"";
    }
    switch(o.type) {
        case msgpack::type::NIL:
            ret += "null";
            break;
            
        case msgpack::type::BOOLEAN:
            ret += (o.via.boolean ? "true" : "false");
            break;
            
        case msgpack::type::POSITIVE_INTEGER: {
            char a[100] = {0};
            sprintf(a, "%llu", o.via.u64);
            ret += a;
        }
            break;
            
        case msgpack::type::NEGATIVE_INTEGER: {
            char a[100] = {0};
            sprintf(a, "%lld", o.via.i64);
            ret += a;
        }
            break;
            
        case msgpack::type::DOUBLE: {
            char a[100] = {0};
            sprintf(a, "%f", o.via.dec);
            ret += a;
        }
            break;
            
        case msgpack::type::RAW: {
            ret += '"';
            std::string str(o.via.raw.ptr, o.via.raw.size);
            for (auto i = 0; i < str.length(); ++i) {
                if (str[i] == '"') {
                    if (i == 0 || str[i - 1] != '\\') {
                        str.replace(i, 1, "\\\"");
                        ++i;
                    }
                }
            }
            ret.append(str);
            ret += '"';
        }
            break;
            
        case msgpack::type::ARRAY:
            ret += "[";
            if(o.via.array.size != 0) {
                msgpack::object* p(o.via.array.ptr);
                msgpack2js(ret, *p);
                ++p;
                for(msgpack::object* const pend(o.via.array.ptr + o.via.array.size);
                    p < pend; ++p) {
                    ret += ",";
                    msgpack2js(ret, *p);
                }
            }
            ret += "]";
            break;
            
        case msgpack::type::MAP:
            ret += "{";
            if(o.via.map.size != 0) {
                msgpack::object_kv* p(o.via.map.ptr);
                msgpack2js(ret, p->key, true);
                ret += ":";
                msgpack2js(ret, p->val);
                ++p;
                for(msgpack::object_kv* const pend(o.via.map.ptr + o.via.map.size);
                    p < pend; ++p) {
                    ret += ",";
                    msgpack2js(ret, p->key, true);
                    ret += ":";
                    msgpack2js(ret, p->val);
                }
            }
            ret += "}";
            break;
            
        default:
            // FIXME
            ret += "#<UNKNOWN ";
            ret += (uint16_t)o.type;
            ret += ">";
    }
    if (asKey && o.type != msgpack::type::RAW) {
        ret += "\"";
    }
}

void js2msgpack(msgpack::packer<msgpack::sbuffer> &packer, const rapidjson::Value &js) {
    if (js.IsArray()) {
        packer.pack_array(js.Size());
        for (auto v = js.onBegin(); v != js.onEnd(); ++v) {
            js2msgpack(packer, *v);
        }
    } else if (js.IsBool()) {
        packer.pack(js.GetBool());
    } else if (js.IsDouble()) {
        packer.pack(js.GetDouble());
    } else if (js.IsInt()) {
        packer.pack(js.GetInt());
    } else if (js.IsInt64()) {
        packer.pack(js.GetInt64());
    } else if (js.IsNull()) {
        packer.pack_nil();
    } else if (js.IsObject()) {
        size_t size = 0;
        for (auto v = js.MemberonBegin(); v != js.MemberonEnd(); ++v) {
            ++size;
        }
        packer.pack_map(size);
        for (auto v = js.MemberonBegin(); v != js.MemberonEnd(); ++v) {
            js2msgpack(packer, v->name);
            js2msgpack(packer, v->value);
        }
    } else if (js.IsString()) {
        packer.pack(std::string(js.GetString()));
    } else if (js.IsUint()) {
        packer.pack(js.GetUint());
    } else if (js.GetUint64()) {
        packer.pack(js.GetUint64());
    }
}

static bool js_cch_restartVM(JSContext *cx, uint32_t argc, jsval *vp)
{
    auto node = Node::create();
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->schedule([=](float){
        scheduler->unscheduleAllForTarget(node);
        ScriptingCore::getInstance()->reset();
        ScriptingCore::getInstance()->runScript("main.js");
    }, node, 0, false, "restartVM");
    return true;
}

static bool js_cch_msgpackToJson(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
	void* arg0;
    
	GLsizei count;
	ok &= JSB_jsval_typedarray_to_dataptr( cx, *argvp++, &count, &arg0, js::ArrayBufferView::TYPE_UINT8);
	JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
    
    msgpack::unpacker unpacker;
    unpacker.reserve_buffer(count);
    memcpy(unpacker.buffer(), arg0, count);
    unpacker.buffer_consumed(count);
    
    std::string ret = "[";
    bool firstItem = true;
    msgpack::unpacked unpacked;
    while (unpacker.next(&unpacked)) {
        if (firstItem) {
            firstItem = false;
        } else {
            ret += ",";
        }
        msgpack2js(ret, unpacked.get());
    }
    ret += "]";
    
    jsval jsret = std_string_to_jsval(cx, ret);
    JS_SET_RVAL(cx, vp, jsret);
    return true;
}

static bool js_cch_jsonToMsgpack(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	bool ok = true;
    std::string arg0;
    
    ok &= jsval_to_std_string(cx, argvp[0], &arg0);
	JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
    
    rapidjson::Document rootValue;
    rootValue.Parse<0>(arg0.c_str());
    
    msgpack::sbuffer buffer;
    msgpack::packer<msgpack::sbuffer> packer(buffer);
    js2msgpack(packer, rootValue);
    
    uint32_t size = static_cast<uint32_t>(buffer.size());
    JSObject* array = JS_NewUint8Array(cx, size);
    if (nullptr == array) {
        JSB_PRECONDITION2(false, cx, false, "Error call JS_NewUint8Array");
    }
    
    uint8_t* bufdata = (uint8_t*)JS_GetArrayBufferViewData(array);
    memcpy(bufdata, buffer.data(), size*sizeof(uint8_t));
    
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(array));
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
    JS_DefineFunction(cx, ns, "msgpackToJson", js_cch_msgpackToJson, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "jsonToMsgpack", js_cch_jsonToMsgpack, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}
