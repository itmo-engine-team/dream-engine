#pragma once

#include <d3d11.h>
#include <wrl/client.h>

class Engine;
class Graphics;

using namespace Microsoft::WRL;

class Shader
{
public:

	Shader(Engine* engine, const wchar_t* shaderPath, D3D11_INPUT_ELEMENT_DESC* inputElements, int elementCount);
	virtual ~Shader() = default;
	
	ComPtr<ID3D11InputLayout> pInputLayout;
	ComPtr<ID3D11VertexShader> pVertexShader;
	ComPtr<ID3D11PixelShader> pPixelShader;

	virtual void SetShader();
	
protected:

	Engine* engine;
	Graphics* graphics;

};

