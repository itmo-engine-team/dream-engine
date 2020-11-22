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
	OrthoWindow(const OrthoWindow&);
	~OrthoWindow();

	bool Initialize(ID3D11Device*, int, int);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*, int, int);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:

	Engine* engine;

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_vertexCount, m_indexCount;

	ID3D11Buffer* constantBuffer;
	ID3D11Buffer* lightBuffer;

	Matrix orthoProjMatrix;
	
};