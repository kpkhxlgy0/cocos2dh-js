#ifndef __HELPER_TOOLS_HLOGFILE_H__
#define __HELPER_TOOLS_HLOGFILE_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

class HLogFile {
public:
    static void clear(const char *file = nullptr);
    static void logFile(const char *str, const char *file = nullptr);
    static std::string getDefaultLogFile();
    static void setEnabled(bool enabled);
private:
    static std::string _logFile;
    static bool _enabled;
};

NS_CC_H_END

#endif // __HELPER_TOOLS_HLOGFILE_H__