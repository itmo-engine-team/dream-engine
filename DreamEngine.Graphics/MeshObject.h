#pragma once

#include <d3d11.h>

#include "MeshData.h"

class Transform;
class Graphics;
struct CameraBuffer;
struct LightBuffer;
struct ConstantBuffer;

class MeshObject
{
public:

    MeshObject(Graphics* graphics, MeshData* meshData);
    ~MeshObject();

    void Render(ConstantBuffer constantBufferData,
        LightBuffer lightBufferData, CameraBuffer cameraBufferData);
    bool RenderShadowMap(ConstantBuffer constantBufferData);

protected:

    Graphics* graphics;
    MeshData* meshData;

    ID3D11Buffer* indexBuffer;
    ID3D11Buffer* vertexBuffer;

    ID3D11Buffer* constantBuffer;
    ID3D11Buffer* lightBuffer;
    ID3D11Buffer* cameraBuffer;
    ID3D11Buffer* modelDataBuffer;
    D3D11_SUBRESOURCE_DATA* csd;

    UINT stride;
    UINT offset = 0u;

};
