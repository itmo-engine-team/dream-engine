#pragma once

#include <d3d11.h>

#include "MeshData.h"
#include <wrl/client.h>

using namespace Microsoft::WRL;

class ModelShader;
class Transform;
class Graphics;
struct CameraBuffer;
struct LightBuffer;
struct ConstantBuffer;

class MeshObject
{
public:

    MeshObject(Graphics* graphics, MeshData* meshData, ModelShader* shader);

    void Render(ConstantBuffer constantBufferData,
        LightBuffer lightBufferData, CameraBuffer cameraBufferData);
    bool RenderShadowMap(ConstantBuffer constantBufferData);

protected:

    MeshData* meshData;
    ModelShader* shader;
    Graphics* graphics;

    ComPtr<ID3D11Buffer> indexBuffer;
    ComPtr<ID3D11Buffer> vertexBuffer;

    ComPtr<ID3D11Buffer> constantBuffer;
    ComPtr<ID3D11Buffer> lightBuffer;
    ComPtr<ID3D11Buffer> cameraBuffer;
    ID3D11Buffer* modelDataBuffer;
    D3D11_SUBRESOURCE_DATA* csd;

    UINT stride;
    UINT offset = 0u;

};
