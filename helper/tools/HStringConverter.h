#ifndef __HSTRINGCONVERTER_H__
#define __HSTRINGCONVERTER_H__
#include "cocos2d.h"
#include "Cocos2dxhMacros.h"
using namespace std;
#define Charset_UTF8		"utf-8"
#define Charset_GBK2312		"gb2312"
NS_CC_H_BEGIN
class HStringConverter
{
public:
	static void WStrToStr(string& OUTstr, const wstring& INwstr);
	static string WStrToStr(const wstring& INwstr);

	static bool IConvConvert(const char* INcharsetTo, const char* INcharsetFrom, const char* INstr, size_t INlenStr, char* OUTstr, size_t OUTlenStr);
	static string IConvConvert_GBKToUTF8(const string& INstr);
	static string IConvConvert_UTF8ToGBK(const string& INstr);

// 	static size_t wstr2cstr(char* OUTstr, const wchar_t* INwstr, size_t INmaxCharCount);
// 	static size_t cstr2wstr(wchar_t* OUTwstr, const char* INstr, size_t INmaxCharCount);
// 	static int wstr2cstr_s(size_t* OUTnumOfCharConverted, char* OUTstr, size_t INsizeOut, const wchar_t* INwstr, size_t INmaxCharCount);
// 	static int cstr2wstr_s(size_t* OUTnumOfCharConverted, wchar_t* OUTwstr, size_t INsizeOut, const char* INstr, size_t INmaxCharCount);
};
NS_CC_H_END
#endif