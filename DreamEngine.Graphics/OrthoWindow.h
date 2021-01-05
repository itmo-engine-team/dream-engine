#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

class Graphics;
class DeferredBuffers;
struct ConstantBuffer;
struct LightBuffer;

class OrthoWindow
{

private:

    struct VertexType
    {
        Vector3 position;
        Vector2 texture;
    };

public:

    OrthoWindow(Graphics* graphics);
    ~OrthoWindow();

    bool Initialize(ID3D11Device* device, int windowWidth, int windowHeight);
    void Shutdown();
    void Render(DeferredBuffers* deferredBuffers,
        ConstantBuffer constantBufferData, LightBuffer lightBufferData);

    int GetIndexCount();

private:

    bool InitializeBuffers(ID3D11Device* device, int windowWidth, int windowHeight);
    void ShutdownBuffers();
    void RenderBuffers(ID3D11DeviceContext* deviceContext,
        ConstantBuffer constantBufferData, LightBuffer lightBufferData);

    Graphics* graphics;

    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;
    int vertexCount, indexCount;

    ID3D11Buffer* constantBuffer;
    ID3D11Buffer* lightBuffer;
    ID3D11Buffer* modelDataBuffer;

    Matrix orthoProjMatrix;
    
};