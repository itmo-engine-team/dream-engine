#pragma once

#include <d3d11.h>

#include "Shader.h"

class LightShader : public Shader
{

public:

	LightShader(Graphics* graphics, const wchar_t* shaderPath);
	~LightShader();

	void Init() override;

	void SetShader(ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture);

private:

	ID3D11SamplerState* samplerState = nullptr;

};