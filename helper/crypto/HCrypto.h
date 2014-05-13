
#ifndef __HELPER_CRYPTO_HCRYPTO_H__
#define __HELPER_CRYPTO_HCRYPTO_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

class HCrypto {    
public:
    static std::string bin2hex(const void *input, size_t inputLen);
    static std::string hex2bin(const std::string &input);

    static size_t getAES256KeyLength(size_t len = 0);
    static void setDefaultKeyAES256_ECB(const void *key, size_t len);
    static std::string encryptAES256_ECB(const std::string &input,
                                         const void *key = nullptr,
                                         size_t keyLen = 0);
    static std::string decryptAES256_ECB(const std::string &input,
                                         const void *key = nullptr,
                                         size_t keyLen = 0);
    
    /** @brief Encrypt data with XXTEA algorithm, return ciphertext, free ciphertext after used */
    static unsigned char* encryptXXTEA(unsigned char* plaintext,
                                       int plaintextLength,
                                       unsigned char* key,
                                       int keyLength,
                                       int* resultLength);
    
    /** @brief Decrypt data with XXTEA algorithm, return plaintext, free plaintext after used */
    static unsigned char* decryptXXTEA(unsigned char* ciphertext,
                                       int ciphertextLength,
                                       unsigned char* key,
                                       int keyLength,
                                       int* resultLength);
    
    /** @brief Encoding data with Base64 algorithm, return encoded string length */
    static std::string encodeBase64(const void *input, size_t inputLen);
    
    
    /** @brief Decoding Base64 string to data, return decoded data length */
    static std::string decodeBase64(const void *input, size_t inputLen);
    
    /** @brief Calculate MD5, get MD5 code (not string) */
    static size_t getMD5BufferLength();
    static void md5(const void *input, int inputLength,
                    unsigned char* output);
    
    /** @brief Calculate SHA1 with a secret key. */
    static size_t getSHA1BufferLength();
    static std::string sha1(unsigned char* input, int inputLength);
    
    static unsigned char toHex(const unsigned char &x);
    static unsigned char fromHex(const unsigned char &x);
    static std::string encodeUrl(const std::string &input);
    static std::string decodeUrl(const std::string &input);
    
#pragma mark -
#pragma mark private methods
    
private:
    HCrypto() {}
private:
    static std::string s_keyAES256_ECB;
};

NS_CC_H_END

#endif // __HELPER_CRYPTO_HCRYPTO_H__
