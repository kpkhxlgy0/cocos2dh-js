#include "HPlatformHelper.h"
#include <uuid/uuid.h>
#import <AVFoundation/AVFoundation.h>

NS_CC_H_BEGIN

void HPlatformHelper::generateUuid(HUuid_t INuuid) {
    uuid_generate(INuuid);
}

void HPlatformHelper::shakeDevice() {
    AudioServicesPlaySystemSound (kSystemSoundID_Vibrate);
}

NS_CC_H_END
