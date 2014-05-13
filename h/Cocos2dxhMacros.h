#ifndef __COCOS2DXHMARCROS_H__
#define __COCOS2DXHMARCROS_H__

#define NS_CC_H_BEGIN                     namespace cocos2d { namespace h {
#define NS_CC_H_END                       }}
#define USING_NS_CC_H                     using namespace cocos2d::h

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

// custom property assign
#define CCB_CUSTOMPROPERTYASSIGNER_GLUE(TARGET, MEMBERVARIABLENAME, MEMBERVARIABLETYPE, MEMBERVARIABLE) \
    if(pTarget == TARGET && strcmp(pMemberVariableName, MEMBERVARIABLENAME) == 0) { \
        MEMBERVARIABLE = pCCBValue->MEMBERVARIABLETYPE; \
        return true; \
    }

// batch member variable assign
#define CCB_MEMBERVARIABLEASSIGNER_GLUE_BATCH(TARGET, MEMBERVARIABLENAMEFORMAT, MEMBERVARIABLENAMECOUNT, MEMBERVARIABLETYPE, MEMBERVARIABLE) \
    for (int i = 0; i < MEMBERVARIABLENAMECOUNT; ++i) { \
        char a[100] = {0}; \
        sprintf(a, MEMBERVARIABLENAMEFORMAT, i); \
        if (pTarget == TARGET && 0 == strcmp(pMemberVariableName, a)) { \
            MEMBERVARIABLETYPE pOldVar = MEMBERVARIABLE[i]; \
            MEMBERVARIABLE[i] = dynamic_cast<MEMBERVARIABLETYPE>(pNode); \
            CC_ASSERT(MEMBERVARIABLE[i]); \
            if (pOldVar != MEMBERVARIABLE[i]) { \
                CC_SAFE_RELEASE(pOldVar); \
                MEMBERVARIABLE[i]->retain(); \
            } \
            return true; \
        } \
    }

// batch custom property assign
#define CCB_CUSTOMPROPERTYASSIGNER_GLUE_BATCH(TARGET, MEMBERVARIABLENAMEFORMAT, MEMBERVARIABLENAMECOUNT, MEMBERVARIABLETYPE, MEMBERVARIABLE) \
    for (int i = 0; i < MEMBERVARIABLENAMECOUNT; ++i) { \
        char a[100] = {0}; \
        sprintf(a, MEMBERVARIABLENAMEFORMAT, i); \
        if(pTarget == TARGET && strcmp(pMemberVariableName, a) == 0) { \
            MEMBERVARIABLE[i] = pCCBValue->MEMBERVARIABLETYPE; \
            return true; \
        } \
    }

#endif // __COCOS2DXHMARCROS_H__
