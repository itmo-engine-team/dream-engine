#pragma once
#include <d3d11.h>
#include "GameObject.h"

class Shader;
class Game;

class RenderedGameObject : public GameObject
{
public:
	
	RenderedGameObject(Game* game, Shader* shader, Vector3 position = Vector3::Zero);
	void init() override;
	void update() override;
	void draw() override;

protected:

	std::vector<Vertex> m_vertices;
	std::vector<DWORD> m_indices;
	ComPtr<ID3D11Buffer> pIndexBuffer;
	ComPtr<ID3D11Buffer> pVertexBuffer;
	UINT indicesCount;

	Shader* m_shader;
	
	ComPtr<ID3D11Buffer> pConstantBuffer;
	ComPtr<ID3D11Buffer> pLightBuffer;
	ComPtr<ID3D11Buffer> pCameraBuffer;
	D3D11_SUBRESOURCE_DATA* csd;
	
	Vector4 m_color;

	UINT stride;
	UINT offset = 0u;
};

