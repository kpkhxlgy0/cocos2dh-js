#ifndef __HELPER_TOOLS_HSHADERCUSTOM_H__
#define __HELPER_TOOLS_HSHADERCUSTOM_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

class HShaderCustom {
public:
    // param: isSprite or is Scale9Sprite
    static GLProgram* createGray(bool isSprite = true);
};

NS_CC_H_END

#endif // __HELPER_TOOLS_HSHADERCUSTOM_H__
