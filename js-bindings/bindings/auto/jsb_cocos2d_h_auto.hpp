#ifndef __cocos2d_h_h__
#define __cocos2d_h_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_cocos2d_h_HAssetsManager_class;
extern JSObject *jsb_cocos2d_h_HAssetsManager_prototype;

bool js_cocos2d_h_HAssetsManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2d_h_HAssetsManager_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2d_h_HAssetsManager(JSContext *cx, JSObject *global);
void register_all_cocos2d_h(JSContext* cx, JSObject* obj);
bool js_cocos2d_h_HAssetsManager_setStoragePath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_setPackageUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_checkUpdate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_getStoragePath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_update(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_setConnectionTimeout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_setVersionFileUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_getPackageUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_getConnectionTimeout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_getVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_getVersionFileUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_deleteVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_HAssetsManager_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_AssetsManagerExt_class;
extern JSObject *jsb_cocos2d_h_AssetsManagerExt_prototype;

bool js_cocos2d_h_AssetsManagerExt_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2d_h_AssetsManagerExt_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2d_h_AssetsManagerExt(JSContext *cx, JSObject *global);
void register_all_cocos2d_h(JSContext* cx, JSObject* obj);
bool js_cocos2d_h_AssetsManagerExt_changeExt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_AssetsManagerExt_removeDirectory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_AssetsManagerExt_getFileSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_AssetsManagerExt_readdir(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_AssetsManagerExt_extname(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_AssetsManagerExt_removeFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_AssetsManagerExt_isDirectory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_AssetsManagerExt_renameFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_AssetsManagerExt_createDirectory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_AssetsManagerExt_dirname(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2d_h_AssetsManagerExt_basename(JSContext *cx, uint32_t argc, jsval *vp);
#endif

