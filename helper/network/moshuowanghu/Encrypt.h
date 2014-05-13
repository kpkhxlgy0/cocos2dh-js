#ifndef __ENCRYPT_HEAD_FILE__
#define __ENCRYPT_HEAD_FILE__

#include "cocos2d.h"

#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

//////////////////////////////////////////////////////////////////////////

//MD5 加密类
class CMD5Encrypt
{
    //函数定义
private:
    //构造函数
    CMD5Encrypt() {}

    //功能函数
public:
    //生成密文
    static void EncryptData(const char *pszSrcData, char szMD5Result[33]);
};

//////////////////////////////////////////////////////////////////////////

//异或加密类
class CXOREncrypt
{
    //函数定义
private:
    //构造函数
    CXOREncrypt() {}

    //功能函数
public:
    //生成密文
    static uint16_t EncryptData(const char *pszSrcData, char *pszEncrypData, uint16_t wSize);
    //解开密文
    static uint16_t CrevasseData(const char *pszEncrypData, char *pszSrcData, uint16_t wSize);
};

//////////////////////////////////////////////////////////////////////////

NS_CC_H_END

#endif