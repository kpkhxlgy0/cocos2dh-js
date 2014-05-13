#include "HActionBlur.h"

#include "../Sprite/HSpriteBlur.h"

NS_CC_H_BEGIN

HActionBlurFromTo* HActionBlurFromTo::create(float duration, float rFrom, float rTo) {
    HActionBlurFromTo *ret = new HActionBlurFromTo();
    ret->initWithDuration(duration, rFrom, rTo);
    ret->autorelease();
    return ret;
}

bool HActionBlurFromTo::initWithDuration(float duration, float rFrom, float rTo) {
    if (ActionInterval::initWithDuration(duration)) {
        _rFrom = rFrom;
        _rTo = rTo;
        return true;
    }
    return false;
}

HActionBlurFromTo* HActionBlurFromTo::clone() const {
	auto a = new HActionBlurFromTo();
	a->initWithDuration(_duration, _rFrom, _rTo);
	a->autorelease();
	return a;
}
HActionBlurFromTo* HActionBlurFromTo::reverse() const {
	auto a = new HActionBlurFromTo();
	a->initWithDuration(_duration, _rTo, _rFrom);
	a->autorelease();
	return a;
}
void HActionBlurFromTo::startWithTarget(Node *target) {
    auto sprite = dynamic_cast<HSpriteBlur*>(target);
    CCASSERT(sprite, "only surpport HSpriteBlur");
    ActionInterval::startWithTarget(target);
    sprite->setBlurSize(_rFrom);
}

void HActionBlurFromTo::update(float time) {
    if (_target) {
        float rCur = _rFrom + (_rTo - _rFrom) * time;
        auto sprite = static_cast<HSpriteBlur*>(_target);
        sprite->setBlurSize(rCur);
    }
}
NS_CC_H_END
