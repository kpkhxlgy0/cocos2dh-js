#ifndef __cocos2dx_h_h__
#define __cocos2dx_h_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_cocos2d_h_HNative_class;
extern JSObject *jsb_cocos2d_h_HNative_prototype;

bool js_cocos2dx_h_HNative_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HNative_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HNative(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HNative_addAlertButton(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNative_openURL(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNative_showActivityIndicator(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNative_hideActivityIndicator(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNative_getDeviceName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNative_vibrate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNative_generateUuid(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNative_getInputText(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNative_cancelAlert(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNative_showAlert(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNative_getOpenUDID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNative_createAlert(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HBFPacket_class;
extern JSObject *jsb_cocos2d_h_HBFPacket_prototype;

bool js_cocos2dx_h_HBFPacket_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HBFPacket_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HBFPacket(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HBFPacket_writeString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HBFPacket_beginWrite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HBFPacket_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HBFPacket_readString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HBFPacket_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HBFPacket_HBFPacket(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HMSPacket_class;
extern JSObject *jsb_cocos2d_h_HMSPacket_prototype;

bool js_cocos2dx_h_HMSPacket_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HMSPacket_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HMSPacket(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HMSPacket_setRoute(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HMSPacket_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HMSPacket_beginWrite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HMSPacket_getRoute(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HMSPacket_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HMSPacket_HMSPacket(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HAssetsManager_class;
extern JSObject *jsb_cocos2d_h_HAssetsManager_prototype;

bool js_cocos2dx_h_HAssetsManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HAssetsManager_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HAssetsManager(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HAssetsManager_setStoragePath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_getDelegate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_checkUpdate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_getStoragePath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_getVersionRemote(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_update(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_setVersionFileUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_getConnectionTimeout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_getVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_getVersionFileUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_setConnectionTimeout(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_setVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_changeExt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_mkdir(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_extname(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_isDirectory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_rmdir(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_dirname(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_basename(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HAssetsManager_HAssetsManager(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HHttpPacker_class;
extern JSObject *jsb_cocos2d_h_HHttpPacker_prototype;

bool js_cocos2dx_h_HHttpPacker_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HHttpPacker_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HHttpPacker(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HHttpPacker_getBase64(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpPacker_packBoolean(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpPacker_packArray(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpPacker_packMap(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpPacker_getStrEncoded(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpPacker_packString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpPacker_packInteger(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpPacker_packDouble(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpPacker_packNil(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpPacker_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpPacker_HHttpPacker(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HHttpRequest_class;
extern JSObject *jsb_cocos2d_h_HHttpRequest_prototype;

bool js_cocos2dx_h_HHttpRequest_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HHttpRequest_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HHttpRequest(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HHttpRequest_addDataParam(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_setTimeoutForConnect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_addPackerParam(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_getTimeoutForRead(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_setTimeoutForRead(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_setUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_addData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_setRequestType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_getTimeoutForConnect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_send(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_addPacker(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_encodeUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_decodeUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpRequest_HHttpRequest(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HHttpResponse_class;
extern JSObject *jsb_cocos2d_h_HHttpResponse_prototype;

bool js_cocos2dx_h_HHttpResponse_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HHttpResponse_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HHttpResponse(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HHttpResponse_getErrorBuffer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpResponse_getResponseDataUnpacked(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpResponse_isSucceed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpResponse_getResponseCode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpResponse_getRequest(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpResponse_getResponseHeader(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HHttpResponse_getResponseData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HNetwork_class;
extern JSObject *jsb_cocos2d_h_HNetwork_prototype;

bool js_cocos2dx_h_HNetwork_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HNetwork_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HNetwork(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HNetwork_isInternetConnectionAvailable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNetwork_isLocalWiFiAvailable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNetwork_getInternetConnectionStatus(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HNetwork_isHostNameReachable(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HSocket_class;
extern JSObject *jsb_cocos2d_h_HSocket_prototype;

bool js_cocos2dx_h_HSocket_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HSocket_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HSocket(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);

extern JSClass  *jsb_cocos2d_h_HSocketManager_class;
extern JSObject *jsb_cocos2d_h_HSocketManager_prototype;

bool js_cocos2dx_h_HSocketManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HSocketManager_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HSocketManager(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HSocketManager_disconnectURL(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HSocketManager_connectIP(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HSocketManager_disconnectIP(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HSocketManager_connectURL(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HSocketManager_end(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HSocketManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HStore_class;
extern JSObject *jsb_cocos2d_h_HStore_prototype;

bool js_cocos2dx_h_HStore_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HStore_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HStore(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HStore_canMakePurchases(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_cancelLoadProducts(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_setReceiptVerifyMode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_restoreCompletedTransactions(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_purchase(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_getReceiptVerifyServerUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_setUserAccount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_setReceiptVerifyServerUrl(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_isProductLoaded(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_getUserAccount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_finishTransaction(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_getReceiptVerifyMode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HStore_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HLogFile_class;
extern JSObject *jsb_cocos2d_h_HLogFile_prototype;

bool js_cocos2dx_h_HLogFile_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HLogFile_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HLogFile(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HLogFile_getDefaultLogFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HLogFile_clear(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HLogFile_logFile(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HShaderCustom_class;
extern JSObject *jsb_cocos2d_h_HShaderCustom_prototype;

bool js_cocos2dx_h_HShaderCustom_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HShaderCustom_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HShaderCustom(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HShaderCustom_createGray(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HActionBlurFromTo_class;
extern JSObject *jsb_cocos2d_h_HActionBlurFromTo_prototype;

bool js_cocos2dx_h_HActionBlurFromTo_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HActionBlurFromTo_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HActionBlurFromTo(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HActionBlurFromTo_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HActionBlurFromTo_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HScale9Sprite_class;
extern JSObject *jsb_cocos2d_h_HScale9Sprite_prototype;

bool js_cocos2dx_h_HScale9Sprite_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HScale9Sprite_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HScale9Sprite(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HScale9Sprite_getScale9Image(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HScale9Sprite_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HScale9Sprite_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HScale9Sprite_createWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HSpriteBlur_class;
extern JSObject *jsb_cocos2d_h_HSpriteBlur_prototype;

bool js_cocos2dx_h_HSpriteBlur_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HSpriteBlur_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HSpriteBlur(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HSpriteBlur_setBlurSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HSpriteBlur_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HSpriteBlur_createWithTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HSpriteBlur_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HSpriteBlur_createWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_h_HWebView_class;
extern JSObject *jsb_cocos2d_h_HWebView_prototype;

bool js_cocos2dx_h_HWebView_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_h_HWebView_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_h_HWebView(JSContext *cx, JSObject *global);
void register_all_cocos2dx_h(JSContext* cx, JSObject* obj);
bool js_cocos2dx_h_HWebView_loadURL(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_setAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_goForward(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_goBack(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_stopLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_canGoBack(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_reload(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_canGoForward(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_isLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_initWithSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_setPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_setVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_setContentSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_h_HWebView_HWebView(JSContext *cx, uint32_t argc, jsval *vp);
#endif

