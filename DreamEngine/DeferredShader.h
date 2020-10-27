//#pragma once
//
//#include <d3d11.h>
//#include <fstream>
//
//#include "Graphics.h"
//#include "SimpleMath.h"
//#include "TexturedShader.h"
//
//using namespace DirectX::SimpleMath;
//
//class DeferredShader : public TexturedShader
//{
//private:
//	struct MatrixBufferType
//	{
//		Matrix world;
//		Matrix view;
//		Matrix projection;
//	};
//
//	struct LightBufferType
//	{
//		Vector3 lightDirection;
//		float padding;
//	};
//
//public:
//	DeferredShader(Graphics* graphics, const wchar_t* shaderPath);
//	~DeferredShader();
//
//	bool Initialize();
//	void Shutdown();
//	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, Matrix worldMatrix, Matrix viewMatrix, Matrix projectionMatrix, ID3D11ShaderResourceView* texture);
//
//private:
//	bool InitializeShader(ID3D11Device* device);
//	void ShutdownShader();
//
//	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, Matrix worldMatrix, Matrix viewMatrix,
//		Matrix projectionMatrix, ID3D11ShaderResourceView* texture);
//
//	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);
//
//	ID3D11VertexShader* vertexShader;
//	ID3D11PixelShader* pixelShader;
//	ID3D11InputLayout* layout;
//	ID3D11SamplerState* sampleStateWrap;
//	ID3D11Buffer* matrixBuffer;
//
//protected:
//	Graphics* graphics = nullptr;
//	std::wstring shaderPath = nullptr;
//};