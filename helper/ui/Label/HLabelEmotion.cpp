/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   xxxx
 @History       (操作 -- 创建)(时间 -- 13-3-19)
 */

#include "HLabelEmotion.h"

USING_NS_CC;
using namespace std;

NS_CC_H_BEGIN

// The return value needs to be deleted by CC_SAFE_DELETE_ARRAY.
static unsigned short *copyUTF16StringN(unsigned short *INstr) {
    int length = INstr ? cc_wcslen(INstr) : 0;
    unsigned short *ret = new unsigned short[length + 1];
    for (int i = 0; i < length; ++i) {
        ret[i] = INstr[i];
    }
    ret[length] = 0;
    return ret;
}

static int findUtf16Chars(unsigned short *INstrSrc, unsigned short *INstrFind) {
    CCAssert(INstrSrc, "");
    CCAssert(INstrFind, "");
    int lenSrc = cc_wcslen(INstrSrc);
    int lenFind = cc_wcslen(INstrFind);
    CCAssert(lenFind <= lenSrc, "");
    for (int i = 0; i < lenSrc - lenFind; ++i) {
        if (INstrSrc[i] == INstrFind[0]) {
            if (memcmp(INstrSrc + i, INstrFind, lenFind) == 0) {
                return i;
            }
        }
    }
    return -1;
}

HLabelEmotion* HLabelEmotion::create(const char *INplistName, const char *INtextureName, const char *INemotionPrefix, int INcountEmotionNumber, const char *INfontName, int INfontSize, const Size &INdimensions, const Color3B &INcolor) {
    HLabelEmotion *ret = new HLabelEmotion();
    if (ret && ret->init(INplistName, INtextureName, INemotionPrefix, INcountEmotionNumber, INfontName, INfontSize, INdimensions, INcolor)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return NULL;
}

HLabelEmotion::HLabelEmotion() : m_batchNode(NULL),
m_emotionPrefixUtf16(NULL),
m_strSrcUtf16(NULL) {

}

HLabelEmotion::~HLabelEmotion() {
    delete [] m_emotionPrefixUtf16;
    delete [] m_strSrcUtf16;
}

bool HLabelEmotion::init(const char *INplistName, const char *INtextureName, const char *INemotionPrefix, int INcountEmotionNumber, const char *INfontName, int INfontSize, const Size &INdimensions, const Color3B& INcolor) {
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(INplistName);
    m_batchNode = CCSpriteBatchNode::create(INtextureName);
    addChild(m_batchNode);
    
    m_emotionPrefixUtf16 = cc_utf8_to_utf16(INemotionPrefix);
    m_countEmotionNumber = INcountEmotionNumber;
    m_fontName = INfontName;
    m_fontSize = INfontSize;
    m_dimensions = INdimensions;
    m_color = INcolor;
    return true;
}

void HLabelEmotion::setString(const std::string &newString) {
    if (m_strSrc.compare(newString)) {
        m_strSrc = newString;
        
        m_strSrcUtf16 = cc_utf8_to_utf16(newString.c_str());
        
        createFontChars();
        updateLabel();
    }
}

const std::string& HLabelEmotion::getString() const {
    return m_strSrc;
}

void HLabelEmotion::createFontChars() {
    for (size_t i = 0; i < m_vecNode.size(); ++i) {
        m_vecNode[i]->removeFromParent();
    }
    m_vecNode.clear();
    
    int indexStr = 0;
    int lenStr = cc_wcslen(m_strSrcUtf16);
    int lenPrefix = cc_wcslen(m_emotionPrefixUtf16) + m_countEmotionNumber;
    m_heightLine = 0;
    while (indexStr < lenStr) {
        int indexFind = findUtf16Chars(m_strSrcUtf16 + indexStr, m_emotionPrefixUtf16);
        if (indexFind > -1 && indexFind <= lenStr - indexStr - lenPrefix) {
            for (int i = 0; i < indexFind; ++i) {
                long items_read, items_write;
                char *strUtf8 = cc_utf16_to_utf8(m_strSrcUtf16 + indexStr, 1, &items_read, &items_write);
                Label *label = Label::createWithSystemFont(strUtf8, m_fontName.c_str(), m_fontSize);
                label->setColor(m_color);
                label->setAnchorPoint(Point(0, 0.5f));
                addChild(label);
                m_vecNode.push_back(label);
                delete [] strUtf8;
                ++indexStr;
                m_heightLine = MAX(m_heightLine, label->getContentSize().height);
            }
            long items_read, items_write;
            char *strUtf8 = cc_utf16_to_utf8(m_strSrcUtf16 + indexStr, lenPrefix, &items_read, &items_write);
            SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(strUtf8);
            if (spriteFrame) {
                Sprite *sprite = Sprite::createWithSpriteFrameName(strUtf8);
                sprite->setAnchorPoint(Point(0, 0.5f));
                m_batchNode->addChild(sprite);
                m_vecNode.push_back(sprite);
                delete [] strUtf8;
                indexStr += lenPrefix;
                m_heightLine = MAX(m_heightLine, sprite->getContentSize().height);
            }
            else {
                long items_read, items_write;
                char *strUtf8 = cc_utf16_to_utf8(m_strSrcUtf16 + indexStr, 1, &items_read, &items_write);
                Label *label = Label::createWithSystemFont(strUtf8, m_fontName.c_str(), m_fontSize);
                label->setColor(m_color);
                label->setAnchorPoint(Point(0, 0.5f));
                addChild(label);
                m_vecNode.push_back(label);
                delete [] strUtf8;
                ++indexStr;
                m_heightLine = MAX(m_heightLine, label->getContentSize().height);
            }
        }
        else {
            for (int i = indexStr; i < lenStr; ++i) {
                long items_read, items_write;
                char *strUtf8 = cc_utf16_to_utf8(m_strSrcUtf16 + indexStr, 1, &items_read, &items_write);
                Label *label = Label::createWithSystemFont(strUtf8, m_fontName.c_str(), m_fontSize);
                label->setColor(m_color);
                label->setAnchorPoint(Point(0, 0.5f));
                addChild(label);
                m_vecNode.push_back(label);
                delete [] strUtf8;
                ++indexStr;
                m_heightLine = MAX(m_heightLine, label->getContentSize().height);
            }
        }
    }
}

void HLabelEmotion::updateLabel() {
    if (m_vecNode.size() == 0) {
        return;
    }
    Point pos(0, m_heightLine * 0.5f);
    Size sizeNode = m_vecNode[0]->getContentSize();
    m_vecNode[0]->setPosition(pos);
    Point posPre = pos;
    Size sizeNodePre = sizeNode;
    int countLine = 1;
    for (size_t i = 1; i < m_vecNode.size(); ++i) {
        pos.x = posPre.x + sizeNodePre.width;
        sizeNode = m_vecNode[i]->getContentSize();
        if (m_dimensions.width > 0 && pos.x > m_dimensions.width) {
            pos.x = 0;
            pos.y -= m_heightLine;
            ++countLine;
        }
        m_vecNode[i]->setPosition(pos);
        posPre = pos;
        sizeNodePre = sizeNode;
    }
    
    Size size(0, countLine * m_heightLine);
    if (m_dimensions.width > 0) {
        size.width = m_dimensions.width;
    }
    else {
        size.width = pos.x + sizeNode.width;
    }
    setContentSize(size);
    if (m_dimensions.width > 0) {
        for (size_t i = 0; i < m_vecNode.size(); ++i) {
            float y = m_vecNode[i]->getPositionY();
            y += (countLine - 1) * m_heightLine;
            m_vecNode[i]->setPositionY(y);
        }
    }
}

NS_CC_H_END
