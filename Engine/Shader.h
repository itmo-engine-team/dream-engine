#pragma once

#include <d3d11.h>
#include <wrl/client.h>

class Game;
class Graphics;

using namespace Microsoft::WRL;

class Shader
{
public:
	Shader(Game* game, const wchar_t* shaderPath, D3D11_INPUT_ELEMENT_DESC* inputElements, int elementCount);
	virtual ~Shader() = default;
	
	ComPtr<ID3D11InputLayout> pInputLayout;
	ComPtr<ID3D11VertexShader> pVertexShader;
	ComPtr<ID3D11PixelShader> pPixelShader;

	virtual void setShader();
	
protected:
	Game* m_game;
	Graphics* graphics;
};

