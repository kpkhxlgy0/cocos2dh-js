/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   xxxx
 @History       (操作 -- 创建)(时间 -- 13-3-19)
 */

#ifndef __HELPER_UI_LABEL_HLABELEMOTION_H__
#define __HELPER_UI_LABEL_HLABELEMOTION_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

class HLabelEmotion : public Node,
public LabelProtocol {
public:
    HLabelEmotion();
    ~HLabelEmotion();
    bool init(const char *INplistName, const char *INtextureName, const char *INemotionPrefix, int INcountEmotionNumber, const char *INfontName, int INfontSize, const Size &INdimensions = Size::ZERO, const Color3B& INcolor = Color3B::WHITE);

    void setString(const std::string &newString) override;
    const std::string& getString() const override;
    
    /** updates the font chars based on the string to render */
    void createFontChars();
    
    void updateLabel();
public:
    static HLabelEmotion* create(const char *INplistName, const char *INtextureName, const char *INemotionPrefix, int INcountEmotionNumber, const char *INfontName, int INfontSize, const Size &INdimensions = Size::ZERO, const Color3B& INcolor = Color3B::WHITE);
private:
    using Node::init;
    
    void parseEmotion();
    void updateString();
private:
    SpriteBatchNode *m_batchNode;
    unsigned short *m_emotionPrefixUtf16;
    int m_countEmotionNumber;
    std::string m_fontName;
    int m_fontSize;
    Size m_dimensions;
    Color3B m_color;
    
    unsigned short *m_strSrcUtf16;
    std::string m_strSrc;
    
    std::vector<Node*> m_vecNode;
    float m_heightLine;
};

NS_CC_H_END

#endif // __HELPER_UI_LABEL_HLABELEMOTION_H__
