#include "HSpriteBlur.h"

NS_CC_H_BEGIN

HSpriteBlur* HSpriteBlur::create() {
    auto ret = new HSpriteBlur();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HSpriteBlur* HSpriteBlur::create(const char *filename) {
    auto ret = new HSpriteBlur();
    if (ret && ret->initWithFile(filename)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HSpriteBlur* HSpriteBlur::create(const char *filename, const Rect& rect) {
    auto ret = new HSpriteBlur();
    if (ret && ret->initWithFile(filename, rect)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HSpriteBlur* HSpriteBlur::createWithTexture(Texture2D *texture) {
    auto ret = new HSpriteBlur();
    if (ret && ret->initWithTexture(texture)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HSpriteBlur* HSpriteBlur::createWithTexture(Texture2D *texture, const Rect& rect) {
    auto ret = new HSpriteBlur();
    if (ret && ret->initWithTexture(texture, rect)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HSpriteBlur* HSpriteBlur::createWithSpriteFrame(SpriteFrame *pSpriteFrame) {
    auto ret = new HSpriteBlur();
    if (ret && ret->initWithSpriteFrame(pSpriteFrame)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HSpriteBlur* HSpriteBlur::createWithSpriteFrameName(const char *spriteFrameName) {
    auto ret = new HSpriteBlur();
    if (ret && ret->initWithSpriteFrameName(spriteFrameName)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

HSpriteBlur::~HSpriteBlur() {
    NotificationCenter::getInstance()->removeObserver(this, EVNET_COME_TO_FOREGROUND);
}

void HSpriteBlur::listenBackToForeground(Ref *obj) {
    setShaderProgram(nullptr);
    initProgram();
}

bool HSpriteBlur::initWithTexture(Texture2D *texture) {
    Rect rect = Rect::ZERO;
    rect.size = texture->getContentSize();
    
    return initWithTexture(texture, rect);
}

bool HSpriteBlur::initWithTexture(Texture2D *texture, const Rect &rect) {
    return initWithTexture(texture, rect, false);
}

bool HSpriteBlur::initWithTexture(Texture2D *texture, const Rect &rect, bool rotated) {
    if(Sprite::initWithTexture(texture, rect, rotated)) {
        NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HSpriteBlur::listenBackToForeground), EVNET_COME_TO_FOREGROUND, nullptr);
        
        auto s = getTexture()->getContentSizeInPixels();

        blur_ = Point(1/s.width, 1/s.height);
        sub_[0] = sub_[1] = sub_[2] = sub_[3] = 0;

        this->initProgram();
        return true;
    }
    return false;
}

void HSpriteBlur::initProgram() {
    const GLchar *fragSource = "// Shader taken from: http://webglsamples.googlecode.com/hg/electricflower/electricflower.html\
    \
#ifdef GL_ES\
    precision mediump float;\
#endif\
    \
    varying vec4 v_fragmentColor;\
    varying vec2 v_texCoord;\
    \
    uniform sampler2D CC_Texture0;\
    \
    uniform vec2 blurSize;\
    uniform vec4 substract;\
    \
    void main() {\
        vec4 sum = vec4(0.0);\
        sum += texture2D(CC_Texture0, v_texCoord - 4.0 * blurSize) * 0.05;\
        sum += texture2D(CC_Texture0, v_texCoord - 3.0 * blurSize) * 0.09;\
        sum += texture2D(CC_Texture0, v_texCoord - 2.0 * blurSize) * 0.12;\
        sum += texture2D(CC_Texture0, v_texCoord - 1.0 * blurSize) * 0.15;\
        sum += texture2D(CC_Texture0, v_texCoord                 ) * 0.16;\
        sum += texture2D(CC_Texture0, v_texCoord + 1.0 * blurSize) * 0.15;\
        sum += texture2D(CC_Texture0, v_texCoord + 2.0 * blurSize) * 0.12;\
        sum += texture2D(CC_Texture0, v_texCoord + 3.0 * blurSize) * 0.09;\
        sum += texture2D(CC_Texture0, v_texCoord + 4.0 * blurSize) * 0.05;\
        \
        gl_FragColor = (sum - substract) * v_fragmentColor;\
    }\
    \
";
    auto pProgram = new GLProgram();
    pProgram->initWithByteArrays(ccPositionTextureColor_vert, fragSource);
    setShaderProgram(pProgram);
    pProgram->release();
    
    CHECK_GL_ERROR_DEBUG();
    
    pProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    pProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    pProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    
    CHECK_GL_ERROR_DEBUG();
    
    pProgram->link();
    
    CHECK_GL_ERROR_DEBUG();
    
    pProgram->updateUniforms();
    
    CHECK_GL_ERROR_DEBUG();
    
    subLocation = glGetUniformLocation(pProgram->getProgram(), "substract");
    blurLocation = glGetUniformLocation(pProgram->getProgram(), "blurSize");
    
    CHECK_GL_ERROR_DEBUG();
}

void HSpriteBlur::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) {
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(HSpriteBlur::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void HSpriteBlur::onDraw(const kmMat4 &transform, bool transformUpdated) {
    GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
    BlendFunc blend = getBlendFunc();
    GL::blendFunc(blend.src, blend.dst);
    
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();
    getShaderProgram()->setUniformLocationWith2f(blurLocation, blur_.x, blur_.y);
    getShaderProgram()->setUniformLocationWith4fv(subLocation, sub_, 1);
    
    GL::bindTexture2D(getTexture()->getName());
    
    //
    // Attributes
    //
#define kQuadSize sizeof(_quad.bl)
    long offset = (long)&_quad;
    
    // vertex
    int diff = offsetof( V3F_C4B_T2F, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    // texCoods
    diff = offsetof( V3F_C4B_T2F, texCoords);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( V3F_C4B_T2F, colors);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    CC_INCREMENT_GL_DRAWS(1);
}

void HSpriteBlur::setBlurSize(float f) {
    auto s = getTexture()->getContentSizeInPixels();

    blur_ = Point(1/s.width, 1/s.height);
    blur_ = blur_ * f;
}

NS_CC_H_END
