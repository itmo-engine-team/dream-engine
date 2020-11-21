#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

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
	OrthoWindow();
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
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
};