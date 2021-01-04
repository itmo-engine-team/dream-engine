#pragma once

#include "DeferredBuffers.h"

struct ConstantBuffer;
struct LightBuffer;
class Graphics;

class SceneRenderer
{

public:

    SceneRenderer(Graphics* graphics);

    ID3D11ShaderResourceView* GetSceneResourceView() const;
    ID3D11ShaderResourceView* GetShadowMapResourceView() const;

    void PrepareDeferredBuffer();
    void PrepareRenderShadowMap();
    void PrepareRenderSceneMap();
    void PrepareRenderScene();

    void RenderScene(ConstantBuffer constantBufferData, LightBuffer lightBufferData);

private:

    const FLOAT SHADOW_MAP_SIZE = 1024;

    Graphics* graphics;
    DeferredBuffers* deferredBuffers;

    // Scene
    D3D11_VIEWPORT sceneViewport;
    ID3D11Texture2D* sceneMap = nullptr;
    ID3D11RenderTargetView* sceneRenderTargetView;
    ID3D11ShaderResourceView* sceneResourceView = nullptr;

    // Shadow Map
    D3D11_VIEWPORT shadowMapViewport;
    ID3D11Texture2D* shadowMap = nullptr;
    ID3D11ShaderResourceView* shadowResourceView = nullptr;
    ID3D11DepthStencilView* shadowDepthView = nullptr;

    void init();
    void initDeferredBuffers();
    void initSceneMap();
    void initShadowMap();

};

