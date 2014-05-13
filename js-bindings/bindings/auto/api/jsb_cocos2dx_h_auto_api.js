/**
 * @module cocos2dx_h
 */
var cch = cch || {};

/**
 * @class HNative
 */
cch.HNative = {

/**
 * @method addAlertButton
 * @param {char} arg0
 * @return {int}
 */
addAlertButton : function (
char 
)
{
    return 0;
},

/**
 * @method openURL
 * @param {char} arg0
 */
openURL : function (
char 
)
{
},

/**
 * @method showActivityIndicator
 */
showActivityIndicator : function (
)
{
},

/**
 * @method hideActivityIndicator
 */
hideActivityIndicator : function (
)
{
},

/**
 * @method getDeviceName
 * @return {String}
 */
getDeviceName : function (
)
{
    return ;
},

/**
 * @method vibrate
 */
vibrate : function (
)
{
},

/**
 * @method generateUuid
 * @return {String}
 */
generateUuid : function (
)
{
    return ;
},

/**
 * @method getInputText
 * @param {char} arg0
 * @param {char} arg1
 * @param {char} arg2
 * @return {String}
 */
getInputText : function (
char, 
char, 
char 
)
{
    return ;
},

/**
 * @method cancelAlert
 */
cancelAlert : function (
)
{
},

/**
 * @method showAlert
 */
showAlert : function (
)
{
},

/**
 * @method getOpenUDID
 * @return {String}
 */
getOpenUDID : function (
)
{
    return ;
},

/**
 * @method createAlert
 * @param {char} arg0
 * @param {char} arg1
 * @param {char} arg2
 */
createAlert : function (
char, 
char, 
char 
)
{
},

};

/**
 * @class HBFPacket
 */
cch.HBFPacket = {

/**
 * @method writeString
 * @param {String} arg0
 */
writeString : function (
str 
)
{
},

/**
 * @method beginWrite
 */
beginWrite : function (
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method readString
 * @return {String}
 */
readString : function (
)
{
    return ;
},

/**
 * @method create
 * @return {cc.h::HBFPacket}
 */
create : function (
)
{
    return cc.h::HBFPacket;
},

/**
 * @method HBFPacket
 * @constructor
 */
HBFPacket : function (
)
{
},

};

/**
 * @class HMSPacket
 */
cch.HMSPacket = {

/**
 * @method setRoute
 * @param {unsigned int} arg0
 */
setRoute : function (
int 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method beginWrite
 */
beginWrite : function (
)
{
},

/**
 * @method getRoute
 * @return {unsigned int}
 */
getRoute : function (
)
{
    return 0;
},

/**
 * @method create
 * @return {cc.h::HMSPacket}
 */
create : function (
)
{
    return cc.h::HMSPacket;
},

/**
 * @method HMSPacket
 * @constructor
 */
HMSPacket : function (
)
{
},

};

/**
 * @class HAssetsManager
 */
cch.HAssetsManager = {

/**
 * @method setStoragePath
 * @param {String} arg0
 */
setStoragePath : function (
str 
)
{
},

/**
 * @method getDelegate
 * @return {cc.h::HAssetsManagerDelegateProtocol}
 */
getDelegate : function (
)
{
    return cc.h::HAssetsManagerDelegateProtocol;
},

/**
 * @method checkUpdate
 * @return {bool}
 */
checkUpdate : function (
)
{
    return false;
},

/**
 * @method getStoragePath
 * @return {String}
 */
getStoragePath : function (
)
{
    return ;
},

/**
 * @method getVersionRemote
 * @return {String}
 */
getVersionRemote : function (
)
{
    return ;
},

/**
 * @method update
 */
update : function (
)
{
},

/**
 * @method setVersionFileUrl
 * @param {String} arg0
 */
setVersionFileUrl : function (
str 
)
{
},

/**
 * @method getConnectionTimeout
 * @return {long}
 */
getConnectionTimeout : function (
)
{
    return 0;
},

/**
 * @method getVersion
 * @return {String}
 */
getVersion : function (
)
{
    return ;
},

/**
 * @method getVersionFileUrl
 * @return {String}
 */
getVersionFileUrl : function (
)
{
    return ;
},

/**
 * @method setConnectionTimeout
 * @param {long} arg0
 */
setConnectionTimeout : function (
long 
)
{
},

/**
 * @method setVersion
 * @param {String} arg0
 */
setVersion : function (
str 
)
{
},

/**
 * @method changeExt
* @param {String|String} str
* @param {String} str
* @return {String|String}
*/
changeExt : function(
str,
str 
)
{
    return ;
},

/**
 * @method create
 * @param {String} arg0
 * @param {String} arg1
 * @param {function} arg2
 * @param {function} arg3
 * @param {function} arg4
 * @param {function} arg5
 * @param {function} arg6
 * @return {cc.h::HAssetsManager}
 */
create : function (
str, 
str, 
func, 
func, 
func, 
func, 
func 
)
{
    return cc.h::HAssetsManager;
},

/**
 * @method mkdir
 * @param {String} arg0
 * @return {bool}
 */
mkdir : function (
str 
)
{
    return false;
},

/**
 * @method extname
 * @param {String} arg0
 * @return {String}
 */
extname : function (
str 
)
{
    return ;
},

/**
 * @method isDirectory
 * @param {String} arg0
 * @return {bool}
 */
isDirectory : function (
str 
)
{
    return false;
},

/**
 * @method rmdir
 * @param {String} arg0
 * @return {bool}
 */
rmdir : function (
str 
)
{
    return false;
},

/**
 * @method dirname
 * @param {String} arg0
 * @return {String}
 */
dirname : function (
str 
)
{
    return ;
},

/**
 * @method basename
 * @param {String} arg0
 * @param {String} arg1
 * @return {String}
 */
basename : function (
str, 
str 
)
{
    return ;
},

/**
 * @method HAssetsManager
 * @constructor
 */
HAssetsManager : function (
)
{
},

};

/**
 * @class HHttpPacker
 */
cch.HHttpPacker = {

/**
 * @method getBase64
 * @return {String}
 */
getBase64 : function (
)
{
    return ;
},

/**
 * @method packBoolean
 * @param {bool} arg0
 */
packBoolean : function (
bool 
)
{
},

/**
 * @method packArray
 * @param {int} arg0
 */
packArray : function (
int 
)
{
},

/**
 * @method packMap
 * @param {int} arg0
 */
packMap : function (
int 
)
{
},

/**
 * @method getStrEncoded
 * @return {String}
 */
getStrEncoded : function (
)
{
    return ;
},

/**
 * @method packString
 * @param {String} arg0
 */
packString : function (
str 
)
{
},

/**
 * @method packInteger
 * @param {int} arg0
 */
packInteger : function (
int 
)
{
},

/**
 * @method packDouble
 * @param {double} arg0
 */
packDouble : function (
double 
)
{
},

/**
 * @method packNil
 */
packNil : function (
)
{
},

/**
 * @method create
 * @return {cc.h::HHttpPacker}
 */
create : function (
)
{
    return cc.h::HHttpPacker;
},

/**
 * @method HHttpPacker
 * @constructor
 */
HHttpPacker : function (
)
{
},

};

/**
 * @class HHttpRequest
 */
cch.HHttpRequest = {

/**
 * @method addDataParam
 * @param {char} arg0
 * @param {String} arg1
 */
addDataParam : function (
char, 
str 
)
{
},

/**
 * @method setTimeoutForConnect
 * @param {int} arg0
 */
setTimeoutForConnect : function (
int 
)
{
},

/**
 * @method addPackerParam
 * @param {char} arg0
 * @param {cc.h::HHttpPacker} arg1
 */
addPackerParam : function (
char, 
hhttppacker 
)
{
},

/**
 * @method getTimeoutForRead
 * @return {int}
 */
getTimeoutForRead : function (
)
{
    return 0;
},

/**
 * @method setTimeoutForRead
 * @param {int} arg0
 */
setTimeoutForRead : function (
int 
)
{
},

/**
 * @method setUrl
 * @param {char} arg0
 */
setUrl : function (
char 
)
{
},

/**
 * @method addData
 * @param {char} arg0
 * @param {String} arg1
 */
addData : function (
char, 
str 
)
{
},

/**
 * @method setRequestType
 * @param {cc.network::HttpRequest::Type} arg0
 */
setRequestType : function (
type 
)
{
},

/**
 * @method getTimeoutForConnect
 * @return {int}
 */
getTimeoutForConnect : function (
)
{
    return 0;
},

/**
 * @method send
 */
send : function (
)
{
},

/**
 * @method addPacker
 * @param {char} arg0
 * @param {cc.h::HHttpPacker} arg1
 */
addPacker : function (
char, 
hhttppacker 
)
{
},

/**
 * @method encodeUrl
 * @param {char} arg0
 * @return {String}
 */
encodeUrl : function (
char 
)
{
    return ;
},

/**
 * @method decodeUrl
 * @param {char} arg0
 * @return {String}
 */
decodeUrl : function (
char 
)
{
    return ;
},

/**
 * @method HHttpRequest
 * @constructor
 */
HHttpRequest : function (
)
{
},

};

/**
 * @class HHttpResponse
 */
cch.HHttpResponse = {

/**
 * @method getErrorBuffer
 * @return {String}
 */
getErrorBuffer : function (
)
{
    return ;
},

/**
 * @method getResponseDataUnpacked
 * @return {String}
 */
getResponseDataUnpacked : function (
)
{
    return ;
},

/**
 * @method isSucceed
 * @return {bool}
 */
isSucceed : function (
)
{
    return false;
},

/**
 * @method getResponseCode
 * @return {int}
 */
getResponseCode : function (
)
{
    return 0;
},

/**
 * @method getRequest
 * @return {cc.h::HHttpRequest}
 */
getRequest : function (
)
{
    return cc.h::HHttpRequest;
},

/**
 * @method getResponseHeader
 * @return {String}
 */
getResponseHeader : function (
)
{
    return ;
},

/**
 * @method getResponseData
 * @return {String}
 */
getResponseData : function (
)
{
    return ;
},

};

/**
 * @class HNetwork
 */
cch.HNetwork = {

/**
 * @method isInternetConnectionAvailable
 * @return {bool}
 */
isInternetConnectionAvailable : function (
)
{
    return false;
},

/**
 * @method isLocalWiFiAvailable
 * @return {bool}
 */
isLocalWiFiAvailable : function (
)
{
    return false;
},

/**
 * @method getInternetConnectionStatus
 * @return {int}
 */
getInternetConnectionStatus : function (
)
{
    return 0;
},

/**
 * @method isHostNameReachable
 * @param {char} arg0
 * @return {bool}
 */
isHostNameReachable : function (
char 
)
{
    return false;
},

};

/**
 * @class HSocket
 */
cch.HSocket = {

};

/**
 * @class HSocketManager
 */
cch.HSocketManager = {

/**
 * @method disconnectURL
 * @param {char} arg0
 * @return {bool}
 */
disconnectURL : function (
char 
)
{
    return false;
},

/**
 * @method connectIP
 * @param {char} arg0
 * @param {int} arg1
 * @param {int} arg2
 * @return {cc.h::HSocket}
 */
connectIP : function (
char, 
int, 
int 
)
{
    return cc.h::HSocket;
},

/**
 * @method disconnectIP
 * @param {char} arg0
 * @param {int} arg1
 * @return {bool}
 */
disconnectIP : function (
char, 
int 
)
{
    return false;
},

/**
 * @method connectURL
 * @param {char} arg0
 * @param {int} arg1
 * @return {cc.h::HSocket}
 */
connectURL : function (
char, 
int 
)
{
    return cc.h::HSocket;
},

/**
 * @method end
 */
end : function (
)
{
},

/**
 * @method getInstance
 * @return {cc.h::HSocketManager}
 */
getInstance : function (
)
{
    return cc.h::HSocketManager;
},

};

/**
 * @class HStore
 */
cch.HStore = {

/**
 * @method canMakePurchases
 * @return {bool}
 */
canMakePurchases : function (
)
{
    return false;
},

/**
 * @method cancelLoadProducts
 */
cancelLoadProducts : function (
)
{
},

/**
 * @method setReceiptVerifyMode
 * @param {cc.h::HStorePaymentTransaction::ReceiptVerifyMode} arg0
 * @param {bool} arg1
 */
setReceiptVerifyMode : function (
receiptverifymode, 
bool 
)
{
},

/**
 * @method restoreCompletedTransactions
 */
restoreCompletedTransactions : function (
)
{
},

/**
 * @method purchase
 * @param {char} arg0
 * @param {int} arg1
 * @return {bool}
 */
purchase : function (
char, 
int 
)
{
    return false;
},

/**
 * @method getReceiptVerifyServerUrl
 * @return {char}
 */
getReceiptVerifyServerUrl : function (
)
{
    return 0;
},

/**
 * @method setUserAccount
 * @param {String} arg0
 */
setUserAccount : function (
str 
)
{
},

/**
 * @method setReceiptVerifyServerUrl
 * @param {char} arg0
 */
setReceiptVerifyServerUrl : function (
char 
)
{
},

/**
 * @method isProductLoaded
 * @param {char} arg0
 * @return {bool}
 */
isProductLoaded : function (
char 
)
{
    return false;
},

/**
 * @method getUserAccount
 * @return {String}
 */
getUserAccount : function (
)
{
    return ;
},

/**
 * @method finishTransaction
 * @param {cc.h::HStorePaymentTransaction} arg0
 */
finishTransaction : function (
hstorepaymenttransaction 
)
{
},

/**
 * @method getReceiptVerifyMode
 * @return {cc.h::HStorePaymentTransaction::ReceiptVerifyMode}
 */
getReceiptVerifyMode : function (
)
{
    return 0;
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method getInstance
 * @return {cc.h::HStore}
 */
getInstance : function (
)
{
    return cc.h::HStore;
},

};

/**
 * @class HLogFile
 */
cch.HLogFile = {

/**
 * @method getDefaultLogFile
 * @return {String}
 */
getDefaultLogFile : function (
)
{
    return ;
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method logFile
 * @param {char} arg0
 * @param {char} arg1
 */
logFile : function (
char, 
char 
)
{
},

};

/**
 * @class HShaderCustom
 */
cch.HShaderCustom = {

/**
 * @method createGray
 * @return {cc.GLProgram}
 */
createGray : function (
)
{
    return cc.GLProgram;
},

};

/**
 * @class HActionBlurFromTo
 */
cch.HActionBlurFromTo = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @return {bool}
 */
initWithDuration : function (
float, 
float, 
float 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @return {cc.h::HActionBlurFromTo}
 */
create : function (
float, 
float, 
float 
)
{
    return cc.h::HActionBlurFromTo;
},

};

/**
 * @class HScale9Sprite
 */
cch.HScale9Sprite = {

/**
 * @method getScale9Image
 * @return {cc.SpriteBatchNode}
 */
getScale9Image : function (
)
{
    return cc.SpriteBatchNode;
},

/**
 * @method create
* @param {char|RectObject|char|char} char
* @param {RectObject|char|RectObject} rect
* @param {RectObject} rect
* @return {cc.h::HScale9Sprite|cc.h::HScale9Sprite|cc.h::HScale9Sprite|cc.h::HScale9Sprite|cc.h::HScale9Sprite}
*/
create : function(
char,
rect,
rect 
)
{
    return cc.h::HScale9Sprite;
},

/**
 * @method createWithSpriteFrameName
* @param {char|char} char
* @param {RectObject} rect
* @return {cc.h::HScale9Sprite|cc.h::HScale9Sprite}
*/
createWithSpriteFrameName : function(
char,
rect 
)
{
    return cc.h::HScale9Sprite;
},

/**
 * @method createWithSpriteFrame
* @param {cc.SpriteFrame|cc.SpriteFrame} spriteframe
* @param {RectObject} rect
* @return {cc.h::HScale9Sprite|cc.h::HScale9Sprite}
*/
createWithSpriteFrame : function(
spriteframe,
rect 
)
{
    return cc.h::HScale9Sprite;
},

};

/**
 * @class HSpriteBlur
 */
cch.HSpriteBlur = {

/**
 * @method setBlurSize
 * @param {float} arg0
 */
setBlurSize : function (
float 
)
{
},

/**
 * @method create
* @param {char|char} char
* @param {RectObject} rect
* @return {cc.h::HSpriteBlur|cc.h::HSpriteBlur|cc.h::HSpriteBlur}
*/
create : function(
char,
rect 
)
{
    return cc.h::HSpriteBlur;
},

/**
 * @method createWithTexture
* @param {cc.Texture2D|cc.Texture2D} texture2d
* @param {RectObject} rect
* @return {cc.h::HSpriteBlur|cc.h::HSpriteBlur}
*/
createWithTexture : function(
texture2d,
rect 
)
{
    return cc.h::HSpriteBlur;
},

/**
 * @method createWithSpriteFrameName
 * @param {char} arg0
 * @return {cc.h::HSpriteBlur}
 */
createWithSpriteFrameName : function (
char 
)
{
    return cc.h::HSpriteBlur;
},

/**
 * @method createWithSpriteFrame
 * @param {cc.SpriteFrame} arg0
 * @return {cc.h::HSpriteBlur}
 */
createWithSpriteFrame : function (
spriteframe 
)
{
    return cc.h::HSpriteBlur;
},

};

/**
 * @class HWebView
 */
cch.HWebView = {

/**
 * @method loadURL
 * @param {char} arg0
 */
loadURL : function (
char 
)
{
},

/**
 * @method setAnchorPoint
 * @param {PointObject} arg0
 */
setAnchorPoint : function (
point 
)
{
},

/**
 * @method goForward
 */
goForward : function (
)
{
},

/**
 * @method goBack
 */
goBack : function (
)
{
},

/**
 * @method stopLoading
 */
stopLoading : function (
)
{
},

/**
 * @method canGoBack
 * @return {bool}
 */
canGoBack : function (
)
{
    return false;
},

/**
 * @method reload
 */
reload : function (
)
{
},

/**
 * @method canGoForward
 * @return {bool}
 */
canGoForward : function (
)
{
    return false;
},

/**
 * @method isLoading
 * @return {bool}
 */
isLoading : function (
)
{
    return false;
},

/**
 * @method initWithSize
 * @param {SizeObject} arg0
 * @return {bool}
 */
initWithSize : function (
size 
)
{
    return false;
},

/**
 * @method setPosition
 * @param {PointObject} arg0
 */
setPosition : function (
point 
)
{
},

/**
 * @method setVisible
 * @param {bool} arg0
 */
setVisible : function (
bool 
)
{
},

/**
 * @method setContentSize
 * @param {SizeObject} arg0
 */
setContentSize : function (
size 
)
{
},

/**
 * @method create
 * @param {SizeObject} arg0
 * @return {cc.h::HWebView}
 */
create : function (
size 
)
{
    return cc.h::HWebView;
},

/**
 * @method HWebView
 * @constructor
 */
HWebView : function (
)
{
},

};
