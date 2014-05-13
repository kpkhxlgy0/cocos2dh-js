#include "HShaderCustom.h"

#define SHADER_PROGRAM_CUSTOM_GRAY "ShaderProgramCustom_Gray"

NS_CC_H_BEGIN

GLProgram* HShaderCustom::createGray(bool isSprite) {
    auto shaderCache = ShaderCache::getInstance();
    const char *shaderName = nullptr;
    if (isSprite) {
        shaderName = SHADER_PROGRAM_CUSTOM_GRAY "_Sprite";
    } else {
        shaderName = SHADER_PROGRAM_CUSTOM_GRAY "_Scale9Sprite";
    }
    auto program = shaderCache->getProgram(shaderName);
    if (program) {
        return program;
    }
    const GLchar* src =
    "#ifdef GL_ES \n \
    precision mediump float; \n \
    #endif \n \
    uniform sampler2D CC_Texture0; \n \
    varying vec2 v_texCoord; \n \
    varying vec4 v_fragmentColor; \n \
    void main(void) \n \
    { \n \
    // Convert to grayscale using NTSC weightings \n \
    vec4 col = texture2D(CC_Texture0, v_texCoord); \n \
    float gray = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n \
    gl_FragColor = vec4(gray, gray, gray, col.a); \n \
    }";
    
    program = new GLProgram();
    if (isSprite) {
        program->initWithByteArrays(ccPositionTextureColor_noMVP_vert, src);
    } else {
        program->initWithByteArrays(ccPositionTextureColor_vert, src);
    }
    program->autorelease();
    CHECK_GL_ERROR_DEBUG();
    
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    CHECK_GL_ERROR_DEBUG();
    
    program->link();
    CHECK_GL_ERROR_DEBUG();
    
    program->updateUniforms();
    CHECK_GL_ERROR_DEBUG();
    
    shaderCache->addProgram(program, shaderName);
    return program;
}

NS_CC_H_END
