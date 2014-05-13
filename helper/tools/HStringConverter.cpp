#include "HStringConverter.h"
#include <iconv.h>
NS_CC_H_BEGIN
void HStringConverter::WStrToStr(string& OUTstr, const wstring& INwstr)
{
	OUTstr.clear();
	for (size_t i = 0; i < INwstr.size(); i++)
	{
		wchar_t w = INwstr[i];
		if (w <= 0x7f)
			OUTstr.push_back((char)w);
		else if (w <= 0x7ff) {
			OUTstr.push_back(0xc0 | ((w >> 6)& 0x1f));
			OUTstr.push_back(0x80| (w & 0x3f));
		}
		else if (w <= 0xffff) {
			OUTstr.push_back(0xe0 | ((w >> 12)& 0x0f));
			OUTstr.push_back(0x80| ((w >> 6) & 0x3f));
			OUTstr.push_back(0x80| (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff) {
			OUTstr.push_back(0xf0 | ((w >> 18)& 0x07)); // wchar_t 4-bytes situation
			OUTstr.push_back(0x80| ((w >> 12) & 0x3f));
			OUTstr.push_back(0x80| ((w >> 6) & 0x3f));
			OUTstr.push_back(0x80| (w & 0x3f));
		}
		else
			OUTstr.push_back('?');
	}
}

string HStringConverter::WStrToStr(const wstring& INwstr)
{
	string temp;
	WStrToStr(temp, INwstr);
	return temp;
}

bool HStringConverter::IConvConvert(const char* INcharsetTo, const char* INcharsetFrom, const char* INstr, size_t INlenStr, char* OUTstr, size_t OUTlenStr)
{
	iconv_t temp = iconv_open(INcharsetTo, INcharsetFrom);
	if (temp == 0)
		return false;
	const char** pin = &INstr;
	char **pout = &OUTstr;
	memset(OUTstr, 0, OUTlenStr);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	size_t ret = iconv(temp, const_cast<char**>(pin), (size_t*)&INlenStr, pout, (size_t*)&OUTlenStr);
#else
	size_t ret = iconv(temp, pin, (size_t*)&INlenStr, pout, (size_t*)&OUTlenStr);
#endif
	iconv_close(temp);
	return ret == (size_t)(-1) ? false : true;
}

std::string HStringConverter::IConvConvert_GBKToUTF8(const string& INstr)
{
	char textOut[256];
	bool ret = IConvConvert(Charset_UTF8, Charset_GBK2312, INstr.c_str(), INstr.length(), textOut, 256);
	return ret ? string(textOut) : string(INstr);
}

std::string HStringConverter::IConvConvert_UTF8ToGBK(const string& INstr)
{
	char textOut[256];
	bool ret = IConvConvert(Charset_GBK2312, Charset_UTF8, INstr.c_str(), INstr.length(),textOut, 256);
	return ret ? string(textOut) : string(INstr);
}

// int HStringConverter::wstr2cstr_s(size_t* OUTnumOfCharConverted, char* OUTstr, size_t INsizeOut, const wchar_t* INwstr, size_t INmaxCharCount)
// {
// 	return wcstombs_s(OUTnumOfCharConverted, OUTstr, INsizeOut, INwstr, INmaxCharCount);
// }

// size_t HStringConverter::wstr2cstr(char* OUTstr, const wchar_t* INwstr, size_t INmaxCharCount)
// {
// 	return wcstombs(OUTstr, INwstr, INmaxCharCount);
// }

// int HStringConverter::cstr2wstr_s(size_t* OUTnumOfCharConverted, wchar_t* OUTwstr, size_t INsizeOut, const char* INstr, size_t INmaxCharCount)
// {
// 	return mbstowcs_s(OUTnumOfCharConverted, OUTwstr, INsizeOut, INstr, INmaxCharCount);
// }

// size_t HStringConverter::cstr2wstr(wchar_t* OUTwstr, const char* INstr, size_t INmaxCharCount)
// {
// 	return mbstowcs(OUTwstr, INstr, INmaxCharCount);
// }

NS_CC_H_END
