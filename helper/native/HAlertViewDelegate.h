
#ifndef __HELPER_NATIVE_HALERTVIEWDELEGATE_H__
#define __HELPER_NATIVE_HALERTVIEWDELEGATE_H__

#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

class HAlertViewDelegate
{
public:
    virtual void alertViewClickedButtonAtIndex(int buttonIndex) = 0;
};

NS_CC_H_END

#endif // __HELPER_NATIVE_HALERTVIEWDELEGATE_H__
