#pragma once
#include "Shader.h"
class Texture;

class TexturedShader :
    public Shader
{
public:

    TexturedShader(Engine* engine,
        const wchar_t* shaderPath,
        D3D11_INPUT_ELEMENT_DESC* inputElements,
        int elementCount,
        Texture* texture);

    void SetShader() override;

protected:

    Texture* m_texture;

};

