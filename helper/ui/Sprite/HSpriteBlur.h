#ifndef __HELPER_UI_SPRITE_HSPRITEBLUR_H__
#define __HELPER_UI_SPRITE_HSPRITEBLUR_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

#define EVNET_COME_TO_FOREGROUND "event_come_to_foreground"

NS_CC_H_BEGIN

class HSpriteBlur : public Sprite {
public:
    ~HSpriteBlur();
    bool initWithTexture(Texture2D *texture) override;
    bool initWithTexture(Texture2D *texture, const Rect &rect) override;
    bool initWithTexture(Texture2D *texture, const Rect &rect, bool rotated) override;
    void setBlurSize(float f);
public:
    static HSpriteBlur* create();
    static HSpriteBlur* create(const char *filename);
    static HSpriteBlur* create(const char *filename, const Rect& rect);
    static HSpriteBlur* createWithTexture(Texture2D *texture);
    static HSpriteBlur* createWithTexture(Texture2D *texture, const Rect& rect);
    static HSpriteBlur* createWithSpriteFrame(SpriteFrame *pSpriteFrame);
    static HSpriteBlur* createWithSpriteFrameName(const char *spriteFrameName);
private:
    void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated);
    void onDraw(const kmMat4 &transform, bool transformUpdated);
    void initProgram();
    void listenBackToForeground(Ref *obj);
private:
    Point blur_;
    GLfloat    sub_[4];

    GLuint    blurLocation;
    GLuint    subLocation;
    
    CustomCommand _customCommand;
};

NS_CC_H_END

#endif // __HELPER_UI_SPRITE_HSPRITEBLUR_H__
