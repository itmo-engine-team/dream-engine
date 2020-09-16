#pragma once
#include "Shader.h"
class Texture;

class TexturedShader :
	public Shader
{
public:
	TexturedShader(Game* game,
		const wchar_t* shaderPath,
		D3D11_INPUT_ELEMENT_DESC* inputElements,
		int elementCount,
		Texture* texture);

	void setShader() override;
	
protected:
	Texture* m_texture;
};

