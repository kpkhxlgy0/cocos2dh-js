#include "HScale9Sprite.h"

NS_CC_H_BEGIN

SpriteBatchNode* HScale9Sprite::getScale9Image() {
    return _scale9Image;
}

HScale9Sprite* HScale9Sprite::create() {
    auto ret = new HScale9Sprite();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}
HScale9Sprite* HScale9Sprite::create(const char* file, Rect rect,  Rect capInsets) {
    auto ret = new HScale9Sprite();
    if (ret && ret->initWithFile(file, rect, capInsets)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}
HScale9Sprite* HScale9Sprite::create(Rect capInsets, const char* file) {
    auto ret = new HScale9Sprite();
    if (ret && ret->initWithFile(capInsets, file)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}
HScale9Sprite* HScale9Sprite::create(const char* file, Rect rect) {
    auto ret = new HScale9Sprite();
    if (ret && ret->initWithFile(file, rect)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}
HScale9Sprite* HScale9Sprite::create(const char* file) {
    auto ret = new HScale9Sprite();
    if (ret && ret->initWithFile(file)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HScale9Sprite* HScale9Sprite::createWithSpriteFrame(SpriteFrame* spriteFrame) {
    auto ret = new HScale9Sprite();
    if (ret && ret->initWithSpriteFrame(spriteFrame)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}
HScale9Sprite* HScale9Sprite::createWithSpriteFrame(SpriteFrame* spriteFrame, Rect capInsets) {
    auto ret = new HScale9Sprite();
    if (ret && ret->initWithSpriteFrame(spriteFrame, capInsets)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HScale9Sprite* HScale9Sprite::createWithSpriteFrameName(const char*spriteFrameName) {
    auto ret = new HScale9Sprite();
    if (ret && ret->initWithSpriteFrameName(spriteFrameName)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}
HScale9Sprite* HScale9Sprite::createWithSpriteFrameName(const char*spriteFrameName, Rect capInsets) {
    auto ret = new HScale9Sprite();
    if (ret && ret->initWithSpriteFrameName(spriteFrameName, capInsets)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

NS_CC_H_END
