#include "HLogFile.h"

#include "../network/HAssetsManager.h"

NS_CC_H_BEGIN

std::string HLogFile::_logFile = "";
bool HLogFile::_enabled = false;

void HLogFile::clear(const char *file) {
    std::string fileName = (file ? file : getDefaultLogFile());
    std::string filePath = FileUtils::getInstance()->getWritablePath() + fileName;
    HAssetsManager::rmdir(filePath.c_str());
}

void HLogFile::logFile(const char *str, const char *file) {
    if (!_enabled) {
        return;
    }
    std::string fileName = (file ? file : getDefaultLogFile());
    std::string filePath = FileUtils::getInstance()->getWritablePath() + fileName;
	FILE *fp = fopen(filePath.c_str(), "ab");
	fwrite(str, strlen(str), 1, fp);
    
    time_t t = time(0);
	struct tm *tp = localtime(&t);
	char a[256] = {0};
	sprintf(a, "\n----- %04d/%02d/%02d %02d:%02d:%02d -----\n\n",
            tp->tm_year + 1900,
            tp->tm_mon + 1,
            tp->tm_mday,
            tp->tm_hour,
            tp->tm_min,
            tp->tm_sec);
	fwrite(a, strlen(a), 1, fp);
    
	fclose(fp);
}

std::string HLogFile::getDefaultLogFile() {
    if (_logFile.empty()) {
        time_t t = time(0);
        struct tm *tp = localtime(&t);
        char a[256] = {0};
        sprintf(a, "log__%04d_%02d_%02d__%02d_%02d_%02d.txt",
                tp->tm_year + 1900,
                tp->tm_mon + 1,
                tp->tm_mday,
                tp->tm_hour,
                tp->tm_min,
                tp->tm_sec);
        _logFile = a;
    }
    return _logFile;
}

void HLogFile::setEnabled(bool enabled) {
    _enabled = enabled;
}

NS_CC_H_END