#include "TexturedShader.h"
#include "Texture.h"

TexturedShader::TexturedShader(Engine* engine,
    const wchar_t* shaderPath,
    D3D11_INPUT_ELEMENT_DESC* inputElements,
    int elementCount,
    Texture* texture)
: Shader(engine, shaderPath, inputElements, elementCount), m_texture(texture)
{
	
}

void TexturedShader::SetShader()
{
    Shader::SetShader();
    m_texture->setTexture();
}
