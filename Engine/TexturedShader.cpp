#include "TexturedShader.h"
#include "Texture.h"

TexturedShader::TexturedShader(Game* game,
    const wchar_t* shaderPath,
    D3D11_INPUT_ELEMENT_DESC* inputElements,
    int elementCount,
    Texture* texture)
: Shader(game, shaderPath, inputElements, elementCount), m_texture(texture)
{
	
}

void TexturedShader::setShader()
{
    Shader::setShader();
    m_texture->setTexture();
}
