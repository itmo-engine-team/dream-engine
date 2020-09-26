#pragma once

#include <d3d11.h>

#include "MeshData.h"
#include "SimpleMath.h"
#include <wrl/client.h>

using namespace Microsoft::WRL;
using namespace DirectX::SimpleMath;

class Game;
class Shader;
class Transform;
class Graphics;

class MeshObject
{
public:

    MeshObject(Game* game, Transform* transform, MeshData* meshData, Shader* shader);

    void Draw();
	
protected:
	Game* game;
	Transform* transform;
	MeshData* meshData;
	Shader* shader;
	Graphics* graphics;

	ComPtr<ID3D11Buffer> pIndexBuffer;
	ComPtr<ID3D11Buffer> pVertexBuffer;

	ComPtr<ID3D11Buffer> pConstantBuffer;
	ComPtr<ID3D11Buffer> pLightBuffer;
	ComPtr<ID3D11Buffer> pCameraBuffer;
	D3D11_SUBRESOURCE_DATA* csd;

	UINT stride;
	UINT offset = 0u;

};

