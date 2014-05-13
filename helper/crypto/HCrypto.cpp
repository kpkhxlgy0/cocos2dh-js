
#include "HCrypto.h"

extern "C" {
#include "xxtea/xxtea.h"
}
#include "../../external/cryptopp/hex.h"
#include "../../external/cryptopp/base64.h"
#include "../../external/cryptopp/aes.h"
#include "../../external/cryptopp/default.h"
#include "../../external/cryptopp/md5.h"
#include "../../external/cryptopp/sha.h"

#include "CCStdC.h"

using std::string;
using namespace CryptoPP;

NS_CC_H_BEGIN

std::string HCrypto::s_keyAES256_ECB = "";

#pragma mark - hex - bin
unsigned char HCrypto::toHex(const unsigned char &x) {
    return x > 9 ? (x - 10 + 'A') : (x + '0');
}

unsigned char HCrypto::fromHex(const unsigned char &x) {
    return isdigit(x) ? (x - '0') : (x - 'A' + 10);
}

string HCrypto::bin2hex(const void *input, size_t inputLen) {
    string ret;
    StringSource((const byte*)input, inputLen, true,
        new HexEncoder(new StringSink(ret)));
    return ret;
}

string HCrypto::hex2bin(const std::string &input) {
    string ret;
    StringSource(input, true,
        new HexDecoder(new StringSink(ret)));
    return ret;
}

#pragma mark - AES256
size_t HCrypto::getAES256KeyLength(size_t len) {
    if (len == 0) {
        return AES::DEFAULT_KEYLENGTH;
    }
    return AES::StaticGetValidKeyLength(len);
}

void HCrypto::setDefaultKeyAES256_ECB(const void *key, size_t len) {
    s_keyAES256_ECB = string((const char*)key, len);
}

string HCrypto::encryptAES256_ECB(const std::string &input,
                                  const void *key,
                                  size_t keyLen) {
    if (!key) {
        key = s_keyAES256_ECB.data();
        keyLen = s_keyAES256_ECB.length();
    }
    string ret;
    ECB_Mode<AES>::Encryption encryptor((const byte*)key, keyLen);
    StringSource(input, true,
                 new StreamTransformationFilter(encryptor,
                                                new StringSink(ret)));
    return ret;
}

string HCrypto::decryptAES256_ECB(const std::string &input,
                                  const void *key,
                                  size_t keyLen) {
    if (!key) {
        key = s_keyAES256_ECB.data();
        keyLen = s_keyAES256_ECB.size();
    }
    string ret;
    ECB_Mode<AES>::Decryption decryptor((const byte*)key, keyLen);
    StringSource(input, true,
                 new StreamTransformationFilter(decryptor,
                                                new StringSink(ret)));
    return ret;
}

#pragma mark - XXTEA
unsigned char* HCrypto::encryptXXTEA(unsigned char* plaintext,
                                      int plaintextLength,
                                      unsigned char* key,
                                      int keyLength,
                                      int* resultLength)
{
    xxtea_long len;
    unsigned char* result = xxtea_encrypt(plaintext, (xxtea_long)plaintextLength, key, (xxtea_long)keyLength, &len);
    *resultLength = (int)len;
    return result;
}

unsigned char* HCrypto::decryptXXTEA(unsigned char* ciphertext,
                                      int ciphertextLength,
                                      unsigned char* key,
                                      int keyLength,
                                      int* resultLength)
{
    xxtea_long len;
    unsigned char* result = xxtea_decrypt(ciphertext, (xxtea_long)ciphertextLength, key, (xxtea_long)keyLength, &len);
    *resultLength = (int)len;
    return result;
}

#pragma mark - base64
std::string HCrypto::encodeBase64(const void *input, size_t inputLen) {
    string ret;
    StringSource((const byte*)input, inputLen, true,
        new Base64Encoder(new StringSink(ret), false));
    return ret;
}

std::string HCrypto::decodeBase64(const void *input, size_t inputLen) {
    string ret;
    StringSource((const byte*)input, inputLen, true,
                 new Base64Decoder(new StringSink(ret)));
    return ret;
}

#pragma mark - md5
size_t HCrypto::getMD5BufferLength() {
    return 16;
}

void HCrypto::md5(const void *input, int inputLength, unsigned char* output) {
    Weak::MD5 md5;
    md5.CalculateDigest(output, (const unsigned char*)input, inputLength);
}

#pragma mark - sha1
size_t HCrypto::getSHA1BufferLength() {
    return 20;
}

string HCrypto::sha1(unsigned char* input, int inputLength) {
    string ret;
    SHA1 sha1;
    StringSource(input, inputLength, true,
        new HashFilter(sha1,
            new HexEncoder(new StringSink(ret))));
    return ret;
}

#pragma mark - url
std::string HCrypto::encodeUrl(const string &input) {
    string ret;
    auto len = input.length();
    auto data = input.data();
    for (size_t i = 0; i < len; ++i) {
        unsigned char buf[4];
        memset(buf, 0, 4);
        if (isalnum(static_cast<unsigned char>(data[i]))) {
            buf[0] = data[i];
        } else if (isspace(static_cast<unsigned char>(data[i]))) {
            buf[0] = '+';
        } else {
            buf[0] = '%';
            buf[1] = toHex(static_cast<unsigned char>(data[i]) >> 4);
            buf[2] = toHex(static_cast<unsigned char>(data[i]) % 16);
        }
        ret += (char *)buf;
    }
    return ret;
}

std::string HCrypto::decodeUrl(const string &input) {
    string ret;
    auto len = input.length();
    auto data = input.data();
    for (size_t i = 0; i < len; ++i) {
        unsigned char ch = 0;
        if (data[i] == '%') {
            ch = fromHex(data[i + 1]) << 4;
            ch |= fromHex(data[i + 2]);
            i += 2;
        } else if(data[i] == '+') {
            ch = ' ';
        }
        else {
            ch = data[i];
        }
        ret += (char)ch;
    }
    return ret;
}

NS_CC_H_END
