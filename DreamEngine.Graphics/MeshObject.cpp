#include "MeshObject.h"

#include <d3dcompiler.h>

#include "ErrorLogger.h"
#include "Graphics.h"

#include "ConstantBuffer.h"
#include "LightBuffer.h"
#include "CameraBuffer.h"
#include "ModelDataBuffer.h"
#include "Texture.h"

MeshObject::MeshObject(Graphics* graphics, MeshData* meshData, Texture* texture)
    : graphics(graphics), meshData(meshData), texture(texture)
{
    topologyType = meshData->IsTriangleTopology() ? D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
                                                  : D3D11_PRIMITIVE_TOPOLOGY_LINELIST;

    HRESULT hr;

    // Create Vertex Buffer
    D3D11_BUFFER_DESC bd = {};
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.CPUAccessFlags = 0u;
    bd.MiscFlags = 0u;
    bd.ByteWidth = meshData->GetVertices().size() * sizeof(Vertex);
    bd.StructureByteStride = sizeof(Vertex);

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = meshData->GetVertices().data();

    hr = graphics->GetDevice()->CreateBuffer(
        &bd,
        &sd,
        &vertexBuffer
    );
    ErrorLogger::DirectXLog(hr, Error, "Failed to create VertexBuffer", __FILE__, __FUNCTION__, __LINE__);

    stride = sizeof(Vertex);

    // Create Index buffer
    D3D11_BUFFER_DESC ibd = {};
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.CPUAccessFlags = 0u;
    ibd.MiscFlags = 0u;
    ibd.ByteWidth = meshData->GetIndices().size() * sizeof(DWORD);
    ibd.StructureByteStride = sizeof(DWORD);

    D3D11_SUBRESOURCE_DATA isd = {};
    isd.pSysMem = meshData->GetIndices().data();

    hr = graphics->GetDevice()->CreateBuffer(
        &ibd,
        &isd,
        &indexBuffer
    );
    ErrorLogger::DirectXLog(hr, Error, "Failed to create IndexBuffer", __FILE__, __FUNCTION__, __LINE__);

    CD3D11_BUFFER_DESC cbd;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.Usage = D3D11_USAGE_DEFAULT;
    cbd.CPUAccessFlags = 0u;
    cbd.MiscFlags = 0u;
    cbd.ByteWidth = sizeof(ConstantBuffer);
    cbd.StructureByteStride = 0u;
    hr = graphics->GetDevice()->CreateBuffer(&cbd, NULL, &constantBuffer);
    ErrorLogger::DirectXLog(hr, Error, "Failed to create ConstantBuffer", __FILE__, __FUNCTION__, __LINE__);

    D3D11_BUFFER_DESC lightBufferDesc;
    lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    lightBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    lightBufferDesc.CPUAccessFlags = 0u;
    lightBufferDesc.MiscFlags = 0;
    lightBufferDesc.ByteWidth = sizeof(LightBuffer);
    lightBufferDesc.StructureByteStride = 0;
    hr = graphics->GetDevice()->CreateBuffer(&lightBufferDesc, NULL, &lightBuffer);
    ErrorLogger::DirectXLog(hr, Error, "Failed to create LightBuffer", __FILE__, __FUNCTION__, __LINE__);

    D3D11_BUFFER_DESC cameraBufferDesc;
    cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cameraBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    cameraBufferDesc.CPUAccessFlags = 0u;
    cameraBufferDesc.MiscFlags = 0;
    cameraBufferDesc.ByteWidth = sizeof(CameraBuffer);
    cameraBufferDesc.StructureByteStride = 0;
    hr = graphics->GetDevice()->CreateBuffer(&cameraBufferDesc, NULL, &cameraBuffer);
    ErrorLogger::DirectXLog(hr, Error, "Failed to create CameraBuffer", __FILE__, __FUNCTION__, __LINE__);

    CD3D11_BUFFER_DESC modelDataBufferDesc;
    modelDataBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    modelDataBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    modelDataBufferDesc.CPUAccessFlags = 0u;
    modelDataBufferDesc.MiscFlags = 0u;
    modelDataBufferDesc.ByteWidth = sizeof(ModelDataBuffer);
    modelDataBufferDesc.StructureByteStride = 0u;
    hr = graphics->GetDevice()->CreateBuffer(&modelDataBufferDesc, NULL, &modelDataBuffer);
    ErrorLogger::DirectXLog(hr, Error, "Failed to create ModelDataBuffer", __FILE__, __FUNCTION__, __LINE__);
}

MeshObject::~MeshObject()
{
    modelDataBuffer->Release();
    indexBuffer->Release();
    vertexBuffer->Release();
    constantBuffer->Release();
    lightBuffer->Release();
    cameraBuffer->Release();
}

void MeshObject::Render(const ConstantBuffer constantBufferData,
                        const LightBuffer lightBufferData, const CameraBuffer cameraBufferData)
{
    graphics->GetContext()->IASetVertexBuffers(
        0u,
        1u,
        &vertexBuffer,
        &stride,
        &offset
    );
    graphics->GetContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0u);
    graphics->GetContext()->IASetPrimitiveTopology(topologyType);

    graphics->GetModelShader()->SetShader();
    if (texture != nullptr && texture->IsValid())
        texture->SetTexture();

    graphics->GetContext()->UpdateSubresource(constantBuffer, 0, NULL, &constantBufferData, 0, 0);
    graphics->GetContext()->VSSetConstantBuffers(0u, 1u, &constantBuffer);

    graphics->GetContext()->UpdateSubresource(lightBuffer, 0, NULL, &lightBufferData, 0, 0);
    graphics->GetContext()->PSSetConstantBuffers(1u, 1u, &lightBuffer);

    graphics->GetContext()->UpdateSubresource(cameraBuffer, 0, NULL, &cameraBufferData, 0, 0);
    graphics->GetContext()->VSSetConstantBuffers(2u, 1u, &cameraBuffer);

    // Update Constant Buffer
    const ModelDataBuffer modelDataBufferData =
    {
        texture != nullptr && texture->IsValid() ? 1.0f : -1.0f,
        graphics->HasLight() ? 1.0f : -1.0f,
        graphics->HasShadow() ? 1.0f : -1.0f,
    };
    graphics->GetContext()->UpdateSubresource(modelDataBuffer, 0, NULL, &modelDataBufferData, 0, 0);
    graphics->GetContext()->PSSetConstantBuffers(3u, 1u, &modelDataBuffer);

    graphics->GetContext()->DrawIndexed(meshData->GetIndicesCount(), 0, 0);
}

bool MeshObject::RenderShadowMap(const ConstantBuffer constantBufferData)
{
    graphics->GetContext()->IASetVertexBuffers(
        0u,
        1u,
        &vertexBuffer,
        &stride,
        &offset
    );
    graphics->GetContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0u);
    graphics->GetContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    graphics->GetContext()->UpdateSubresource(constantBuffer, 0, NULL, &constantBufferData, 0, 0);
    graphics->GetContext()->VSSetConstantBuffers(0u, 1u, &constantBuffer);

    graphics->GetContext()->DrawIndexed(meshData->GetIndicesCount(), 0, 0);

    return true;
}

void MeshObject::SetTexture(Texture* texture)
{
    this->texture = texture;
}
