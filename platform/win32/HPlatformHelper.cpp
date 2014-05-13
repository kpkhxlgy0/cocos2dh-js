#include "../../helper/tools/HPlatformHelper.h"

NS_CC_H_BEGIN

void HPlatformHelper::generateUuid(HUuid_t INuuid) {
    GUID ret;
    CoCreateGuid(&ret);
    memcpy(INuuid, &ret, 16);
}

void HPlatformHelper::shakeDevice() {
    CCLOG("not surpport in windows");
}

NS_CC_H_END
