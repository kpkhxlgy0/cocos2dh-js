#ifndef __HELPER_UI_SCALE9SPRITE_HSCALE9SPRITE_H__
#define __HELPER_UI_SCALE9SPRITE_HSCALE9SPRITE_H__

#include "cocos-ext.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

class HScale9Sprite : public extension::Scale9Sprite {
public:
    SpriteBatchNode* getScale9Image();
public:
    static HScale9Sprite* create();
    static HScale9Sprite* create(const char* file, Rect rect,  Rect capInsets);
    static HScale9Sprite* create(Rect capInsets, const char* file);
    static HScale9Sprite* create(const char* file, Rect rect);
    static HScale9Sprite* create(const char* file);

    static HScale9Sprite* createWithSpriteFrame(SpriteFrame* spriteFrame);
    static HScale9Sprite* createWithSpriteFrame(SpriteFrame* spriteFrame, Rect capInsets);
    
    static HScale9Sprite* createWithSpriteFrameName(const char*spriteFrameName);
    static HScale9Sprite* createWithSpriteFrameName(const char*spriteFrameName, Rect capInsets);
};

NS_CC_H_END

#endif // __HELPER_UI_SCALE9SPRITE_HSCALE9SPRITE_H__
