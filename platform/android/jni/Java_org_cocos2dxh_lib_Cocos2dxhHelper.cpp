#include "CCDirector.h"
#include "platform/CCFileUtils.h"
#include "CCEventType.h"
#include "support/CCNotificationCenter.h"
#include "../../../../cocos2dx/platform/android/jni/JniHelper.h"
#include <jni.h>

#define  CLASS_NAME "org/cocos2dxh/lib/Cocos2dxhHelper"

using namespace cocos2d;
using namespace std;

string generateUuidJNI() {
    JniMethodInfo t;
    string ret;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "generateUuid", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    return ret;
}
string getOpenUDIDJNI() {
    JniMethodInfo t;
    string ret;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getOpenUDID", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    return ret;
}
void vibrateJNI() {
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "vibrate", "()V")) {
        t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}
