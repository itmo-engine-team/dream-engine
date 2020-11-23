#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Engine;
using namespace  DirectX::SimpleMath;

class OrthoWindow
{

private:

	struct VertexType
	{
		Vector3 position;
		Vector2 texture;
	};

public:

	OrthoWindow(Engine* engine);
	~OrthoWindow();

	bool Initialize(ID3D11Device* device, int windowWidth, int windowHeight);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();

private:

	bool InitializeBuffers(ID3D11Device* device, int windowWidth, int windowHeight);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

	Engine* engine;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int vertexCount, indexCount;

	ID3D11Buffer* constantBuffer;
	ID3D11Buffer* lightBuffer;

	Matrix orthoProjMatrix;
	
};