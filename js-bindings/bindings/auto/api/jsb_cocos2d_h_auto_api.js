/**
 * @module cocos2d_h
 */
var cch = cch || {};

/**
 * @class HAssetsManager
 */
cch.HAssetsManager = {

/**
 * @method setStoragePath
 * @param {char} arg0
 */
setStoragePath : function (
char 
)
{
},

/**
 * @method setPackageUrl
 * @param {char} arg0
 */
setPackageUrl : function (
char 
)
{
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
 * @return {char}
 */
getStoragePath : function (
)
{
    return 0;
},

/**
 * @method update
 */
update : function (
)
{
},

/**
 * @method setConnectionTimeout
 * @param {unsigned int} arg0
 */
setConnectionTimeout : function (
int 
)
{
},

/**
 * @method setVersionFileUrl
 * @param {char} arg0
 */
setVersionFileUrl : function (
char 
)
{
},

/**
 * @method getPackageUrl
 * @return {char}
 */
getPackageUrl : function (
)
{
    return 0;
},

/**
 * @method getConnectionTimeout
 * @return {unsigned int}
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
 * @return {char}
 */
getVersionFileUrl : function (
)
{
    return 0;
},

/**
 * @method deleteVersion
 */
deleteVersion : function (
)
{
},

/**
 * @method create
 * @param {char} arg0
 * @param {char} arg1
 * @param {char} arg2
 * @param {function} arg3
 * @param {function} arg4
 * @param {function} arg5
 * @return {cc.h::HAssetsManager}
 */
create : function (
char, 
char, 
char, 
func, 
func, 
func 
)
{
    return cc.h::HAssetsManager;
},

};

/**
 * @class AssetsManagerExt
 */
cch.AssetsManagerExt = {

/**
 * @method changeExt
 * @param {String} arg0
 * @param {String} arg1
 * @return {String}
 */
changeExt : function (
str, 
str 
)
{
    return ;
},

/**
 * @method removeDirectory
 * @param {String} arg0
 * @return {bool}
 */
removeDirectory : function (
str 
)
{
    return false;
},

/**
 * @method getFileSize
 * @param {String} arg0
 * @return {long}
 */
getFileSize : function (
str 
)
{
    return 0;
},

/**
 * @method readdir
 * @param {String} arg0
 * @param {bool} arg1
 * @return {Array}
 */
readdir : function (
str, 
bool 
)
{
    return new Array();
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
 * @method removeFile
 * @param {String} arg0
 * @return {bool}
 */
removeFile : function (
str 
)
{
    return false;
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
 * @method renameFile
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @return {bool}
 */
renameFile : function (
str, 
str, 
str 
)
{
    return false;
},

/**
 * @method createDirectory
 * @param {String} arg0
 * @return {bool}
 */
createDirectory : function (
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

};
