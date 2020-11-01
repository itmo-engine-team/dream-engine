#pragma once

#include <d3d11.h>

#include "MeshData.h"
#include "SimpleMath.h"
#include <wrl/client.h>

using namespace Microsoft::WRL;
using namespace DirectX::SimpleMath;

class Engine;
class Shader;
class Transform;
class Graphics;

class MeshObject
{
public:

    MeshObject(Engine* engine, Transform* transform, MeshData* meshData, Shader* shader);

    void Draw();
    bool RenderShadowMap();
    bool RenderDeferred();

protected:

    Engine* engine;
    Transform* transform;
    MeshData* meshData;
    Shader* shader;
    Graphics* graphics;

    ComPtr<ID3D11Buffer> indexBuffer;
    ComPtr<ID3D11Buffer> vertexBuffer;

    ComPtr<ID3D11Buffer> constantBuffer;
    ComPtr<ID3D11Buffer> lightBuffer;
    ComPtr<ID3D11Buffer> cameraBuffer;
    D3D11_SUBRESOURCE_DATA* csd;

    UINT stride;
    UINT offset = 0u;

};

