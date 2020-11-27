#include "OrthoWindow.h"

#include "Graphics.h"

#include "ErrorLogger.h"
#include "LightBuffer.h"
#include "ConstantBuffer.h"
#include "ModelDataBuffer.h"

OrthoWindow::OrthoWindow(Graphics* graphics) : graphics(graphics)
{
    vertexBuffer = nullptr;
    indexBuffer = nullptr;

    orthoProjMatrix = Matrix::CreateOrthographic(
        graphics->GetWindow()->GetScreenWidth(),
        graphics->GetWindow()->GetScreenHeight(),
        0.1f, 1000.0f
    );
}

OrthoWindow::~OrthoWindow()
{
}

bool OrthoWindow::Initialize(ID3D11Device* device, int windowWidth, int windowHeight)
{
    bool result;

    // Initialize the vertex and index buffer that hold the geometry for the ortho window model.
    result = InitializeBuffers(device, windowWidth, windowHeight);
    if (!result)
    {
        ErrorLogger::Log(Error, "Failed to initialize vertex and index buffer");
        return false;
    }

    return true;
}

void OrthoWindow::Shutdown()
{
    // Release the vertex and index buffers.
    ShutdownBuffers();
}

void OrthoWindow::Render(ID3D11DeviceContext* deviceContext,
    ConstantBuffer constantBufferData, LightBuffer lightBufferData)
{
    graphics->GetLightShader()->SetShader(graphics->GetDeferredBuffers());

    // Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
    RenderBuffers(deviceContext, constantBufferData, lightBufferData);

    graphics->GetContext()->DrawIndexed(GetIndexCount(), 0, 0);
}

int OrthoWindow::GetIndexCount()
{
    return indexCount;
}

bool OrthoWindow::InitializeBuffers(ID3D11Device* device, int windowWidth, int windowHeight)
{
    float left, right, top, bottom;
    VertexType* vertices;
    unsigned long* indices;
    D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
    HRESULT result;

    // Calculate the screen coordinates of the left side of the window.
    left = static_cast<float>((windowWidth / 2) * -1);

    // Calculate the screen coordinates of the right side of the window.
    right = left + static_cast<float>(windowWidth);

    // Calculate the screen coordinates of the top of the window.
    top = static_cast<float>(windowHeight / 2);

    // Calculate the screen coordinates of the bottom of the window.
    bottom = top - static_cast<float>(windowHeight);

    // Set the number of vertices in the vertex array.
    vertexCount = 6;

    // Set the number of indices in the index array.
    indexCount = vertexCount;

    // Create the vertex array.
    vertices = new VertexType[vertexCount];
    if (!vertices)
    {
        ErrorLogger::Log(Error, "Failed to create vertex array in ortho window.");
        return false;
    }

    // Create the index array.
    indices = new unsigned long[indexCount];
    if (!indices)
    {
        ErrorLogger::Log(Error, "Failed to create index array in ortho window.");
        return false;
    }

    // Load the vertex array with data.
    
    // First triangle.
    // Top left.
    vertices[0].position = Vector3(left, top, 0.0f);  
    vertices[0].texture = Vector2(0.0f, 0.0f);

    // Bottom right.
    vertices[1].position = Vector3(right, bottom, 0.0f);  
    vertices[1].texture = Vector2(1.0f, 1.0f);

    // Bottom left.
    vertices[2].position = Vector3(left, bottom, 0.0f);  
    vertices[2].texture = Vector2(0.0f, 1.0f);

    // Second triangle.
    // Top left.
    vertices[3].position = Vector3(left, top, 0.0f);  
    vertices[3].texture = Vector2(0.0f, 0.0f);

    // Top right.
    vertices[4].position = Vector3(right, top, 0.0f);  
    vertices[4].texture = Vector2(1.0f, 0.0f);

    // Bottom right.
    vertices[5].position = Vector3(right, bottom, 0.0f);  
    vertices[5].texture = Vector2(1.0f, 1.0f);

    // Load the index array with data.
    for (int i = 0; i < indexCount; i++)
    {
        indices[i] = i;
    }

    // Set up the description of the vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    // Now finally create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
    if (FAILED(result))
    {
        ErrorLogger::DirectXLog(result, Error, "Failed to create vertex buffer", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    // Set up the description of the index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    // Create the index buffer.
    result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
    if (FAILED(result))
    {
        ErrorLogger::DirectXLog(result, Error, "Failed to create index buffer", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    // Release the arrays now that the vertex and index buffers have been created and loaded.
    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;

    CD3D11_BUFFER_DESC cbd;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.Usage = D3D11_USAGE_DEFAULT;
    cbd.CPUAccessFlags = 0u;
    cbd.MiscFlags = 0u;
    cbd.ByteWidth = sizeof(ConstantBuffer);
    cbd.StructureByteStride = 0u;
    result = device->CreateBuffer(&cbd, NULL, &constantBuffer);
    ErrorLogger::DirectXLog(result, Error, "Failed to create ConstantBuffer", __FILE__, __FUNCTION__, __LINE__);

    D3D11_BUFFER_DESC lightBufferDesc;
    lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    lightBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    lightBufferDesc.CPUAccessFlags = 0u;
    lightBufferDesc.MiscFlags = 0;
    lightBufferDesc.ByteWidth = sizeof(LightBuffer);
    lightBufferDesc.StructureByteStride = 0;
    result = device->CreateBuffer(&lightBufferDesc, NULL, &lightBuffer);
    ErrorLogger::DirectXLog(result, Error, "Failed to create LightBuffer", __FILE__, __FUNCTION__, __LINE__);

    CD3D11_BUFFER_DESC modelDataBufferDesc;
    modelDataBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    modelDataBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    modelDataBufferDesc.CPUAccessFlags = 0u;
    modelDataBufferDesc.MiscFlags = 0u;
    modelDataBufferDesc.ByteWidth = sizeof(ModelDataBuffer);
    modelDataBufferDesc.StructureByteStride = 0u;
    result = device->CreateBuffer(&modelDataBufferDesc, NULL, &modelDataBuffer);
    ErrorLogger::DirectXLog(result, Error, "Failed to create ModelDataBuffer", __FILE__, __FUNCTION__, __LINE__);

    return true;
}

void OrthoWindow::ShutdownBuffers()
{
    // Release the index buffer.
    if (indexBuffer)
    {
        indexBuffer->Release();
        indexBuffer = 0;
    }

    // Release the vertex buffer.
    if (vertexBuffer)
    {
        vertexBuffer->Release();
        vertexBuffer = 0;
    }
}

void OrthoWindow::RenderBuffers(ID3D11DeviceContext* deviceContext, 
    ConstantBuffer constantBufferData, LightBuffer lightBufferData)
{
    unsigned int stride;
    unsigned int offset;

    // Set vertex buffer stride and offset.
    stride = sizeof(VertexType);
    offset = 0;

    // Set the vertex buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Update Constant Buffer
    constantBufferData.ProjectionMatrix = orthoProjMatrix;
    deviceContext->UpdateSubresource(constantBuffer, 0, NULL, &constantBufferData, 0, 0);
    deviceContext->VSSetConstantBuffers(0u, 1u, &constantBuffer);

    deviceContext->UpdateSubresource(lightBuffer, 0, NULL, &lightBufferData, 0, 0);
    deviceContext->PSSetConstantBuffers(1u, 1u, &lightBuffer);

    // Update Constant Buffer
    const ModelDataBuffer modelDataBufferData =
    {
        0.0f,  // not using
        graphics->HasLight() ? 1.0f : -1.0f,
        graphics->HasShadow() ? 1.0f : -1.0f,
    };
    deviceContext->UpdateSubresource(modelDataBuffer, 0, NULL, &modelDataBufferData, 0, 0);
    deviceContext->PSSetConstantBuffers(2u, 1u, &modelDataBuffer);
}