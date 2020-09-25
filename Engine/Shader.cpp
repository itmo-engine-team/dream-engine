#include "Game.h"
#include "Shader.h"
#include <iostream>
#include <d3dcompiler.h>

Shader::Shader(Game* game, const wchar_t* shaderPath, D3D11_INPUT_ELEMENT_DESC* inputElements, int elementCount)
	: m_game(game)
{
	ID3DBlob* vertexBC;
	ID3DBlob* errorVertexCode;
	auto hr = D3DCompileFromFile(shaderPath,
		nullptr /*macros*/,
		nullptr /*include*/,
		"VSMain",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR,
		0,
		&vertexBC,
		&errorVertexCode);

	if (FAILED(hr)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(m_game->hWnd, shaderPath, L"Missing Shader File", MB_OK);
		}
		return;
	}

	m_game->graphics->device->CreateVertexShader(
		vertexBC->GetBufferPointer(),
		vertexBC->GetBufferSize(),
		nullptr,
		&pVertexShader
		);

	//D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };

	ID3DBlob* pixelBC;
	ID3DBlob* errorPixelCode;
	hr = D3DCompileFromFile(shaderPath,
		nullptr/*Shader_Macros /*macros*/, nullptr /*include*/,
		"PSMain", "ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR,
		0, &pixelBC, &errorPixelCode);

	if (FAILED(hr)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorPixelCode) {
			char* compileErrors = (char*)(errorPixelCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(m_game->hWnd, shaderPath, L"Missing Shader File", MB_OK);
		}
		return;
	}

	hr = m_game->graphics->device->CreatePixelShader(
		pixelBC->GetBufferPointer(),
		pixelBC->GetBufferSize(),
		nullptr,
		&pPixelShader
		);

	ID3D11InputLayout* layout;
	hr = m_game->graphics->device->CreateInputLayout(
		inputElements,
		elementCount,
		vertexBC->GetBufferPointer(),
		vertexBC->GetBufferSize(),
		&pInputLayout);
}

void Shader::setShader()
{
	m_game->graphics->context->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	m_game->graphics->context->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	m_game->graphics->context->IASetInputLayout(pInputLayout.Get());
}
