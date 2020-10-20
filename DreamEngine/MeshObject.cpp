#include "MeshObject.h"

#include <d3dcompiler.h>

#include "Engine.h"

#include "Shader.h"
#include "ConstantBuffer.h"
#include "LightBuffer.h"
#include "CameraBuffer.h"
#include "Vertex.h"

#include "ErrorLogger.h"

MeshObject::MeshObject(Engine* engine, Transform* transform, MeshData* meshData, Shader* shader)
    : engine(engine), transform(transform), meshData(meshData), shader(shader)
{
    graphics = engine->GetGraphics();

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
        vertexBuffer.GetAddressOf()
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
        indexBuffer.GetAddressOf()
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

}

void MeshObject::Draw()
{
    graphics->GetContext()->IASetVertexBuffers(
        0u,
        1u,
        vertexBuffer.GetAddressOf(),
        &stride,
        &offset
        );
    graphics->GetContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
    graphics->GetContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    shader->SetShader();

    // Update Constant Buffer
    const ConstantBuffer cb =
    {
        transform->GetWorldMatrix(),
        engine->GetGame()->GetCamera()->GetViewMatrix(),
        engine->GetGame()->GetCamera()->GetProjectionMatrix(),
    };
    graphics->GetContext()->UpdateSubresource(constantBuffer.Get(), 0, NULL, &cb, 0, 0);
    graphics->GetContext()->VSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());

    const LightBuffer lb =
    {
        Vector4{0.15f, 0.15f, 0.15f, 1.0f},
        Vector4{1.0f, 1.0f, 1.0f, 1.0f},
        Vector3{0.0f, -1.0f, 0.0f},
        100.0f,
        {1.0f, 1.0f, 1.0f, 1.0f }
    };
    graphics->GetContext()->UpdateSubresource(lightBuffer.Get(), 0, NULL, &lb, 0, 0);
    graphics->GetContext()->PSSetConstantBuffers(1u, 1u, lightBuffer.GetAddressOf());

    // Update Constant Buffer
    const CameraBuffer cameraBufferData =
    {
        engine->GetGame()->GetCamera()->GetTransform()->GetWorldPosition(),
        0.0f
    };

    graphics->GetContext()->UpdateSubresource(cameraBuffer.Get(), 0, NULL, &cameraBufferData, 0, 0);
    graphics->GetContext()->VSSetConstantBuffers(2u, 1u, cameraBuffer.GetAddressOf());

    graphics->GetContext()->DrawIndexed(meshData->GetIndicesCount(), 0, 0);
}

bool MeshObject::RenderShadowMap()
{
    graphics->GetContext()->IASetVertexBuffers(
        0u,
        1u,
        vertexBuffer.GetAddressOf(),
        &stride,
        &offset
    );
    graphics->GetContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
    graphics->GetContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    const ConstantBuffer cb =
    {
        transform->GetWorldMatrix(),
        engine->GetGame()->GetCamera()->GetViewMatrix(), // TODO от источника света :D -> копия от камеры - свет
        engine->GetGame()->GetCamera()->GetProjectionMatrix(),
    };
    graphics->GetContext()->UpdateSubresource(constantBuffer.Get(), 0, NULL, &cb, 0, 0);
    graphics->GetContext()->VSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());

    graphics->GetContext()->DrawIndexed(meshData->GetIndicesCount(), 0, 0);

    return true;
}
