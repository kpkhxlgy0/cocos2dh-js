#ifndef __HELPER_UI_ACTION_HACTIONBLUR_H__
#define __HELPER_UI_ACTION_HACTIONBLUR_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

class HActionBlurFromTo : public ActionInterval {
public:
    bool initWithDuration(float duration, float rFrom, float rTo);
    
    virtual HActionBlurFromTo* clone() const override;
	virtual HActionBlurFromTo* reverse(void) const override;
public:
    static HActionBlurFromTo* create(float duration, float rFrom, float rTo);
private:
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
protected:
    float _rFrom;
    float _rTo;
};
NS_CC_H_END
#endif // __HELPER_UI_ACTION_HACTIONBLUR_H__
