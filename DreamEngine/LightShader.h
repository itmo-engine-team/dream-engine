#pragma once
#include <d3d11.h>
#include <fstream>

#include "SimpleMath.h"
#include "Graphics.h"
#include "ModelShader.h"

using namespace DirectX::SimpleMath;

class LightShader : public ModelShader
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
		Vector4 ambientColor;
		Vector4 diffuseColor;
		float specularPower;
		Vector4 specularColor;
		Vector3 lightDirection;
		float padding;
	};

public:
	LightShader(Graphics* graphics, const wchar_t* shaderPath, Texture* texture);
	~LightShader();

	bool Initialize();
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, Matrix worldMatrix, Matrix viewMatrix,
		Matrix projectionMatrix, ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture,
		Vector3 lightDirection);

private:
	bool InitializeShader(ID3D11Device* device,const wchar_t* fxFileName);
	void ShutdownShader();

	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, Matrix worldMatrix, Matrix viewMatrix,
		Matrix projectionMatrix, ID3D11ShaderResourceView* colorTexture,
		ID3D11ShaderResourceView* normalTexture, Vector3 lightDirection);
	void RenderShader(ID3D11DeviceContext*, int);

	//ID3D11VertexShader* vertexShader;
	//ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* lightBuffer;

protected:
	//Graphics* graphics = nullptr;
};