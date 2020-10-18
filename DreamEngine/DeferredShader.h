#pragma once

#include <d3d11.h>
#include "SimpleMath.h"
//#include <d3dx11async.h>
#include <fstream>

using namespace DirectX::SimpleMath;

class DeferredShader
{
private:
	struct MatrixBufferType
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	struct LightBufferType
	{
		Vector3 lightDirection;
		float padding;
	};

public:
	DeferredShader();
	DeferredShader(const DeferredShader& other);
	~DeferredShader();

	bool Initialize(ID3D11Device* device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, Matrix worldMatrix, Matrix viewMatrix, Matrix projectionMatrix, ID3D11ShaderResourceView* texture);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, const wchar_t* fxFileName);
	void ShutdownShader();

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, Matrix worldMatrix, Matrix viewMatrix,
		Matrix projectionMatrix, ID3D11ShaderResourceView* texture);

	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;
	ID3D11SamplerState* sampleStateWrap;
	ID3D11Buffer* matrixBuffer;
};