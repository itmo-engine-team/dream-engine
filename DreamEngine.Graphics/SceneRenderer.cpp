#include "SceneRenderer.h"
#include "Graphics.h"
#include "ErrorLogger.h"
#include "ConstantBuffer.h"
#include "LightBuffer.h"

SceneRenderer::SceneRenderer(Graphics* graphics) : graphics(graphics)
{
    init();
}

ID3D11ShaderResourceView* SceneRenderer::GetSceneResourceView() const
{
    return sceneResourceView;
}

ID3D11ShaderResourceView* SceneRenderer::GetShadowMapResourceView() const
{
    return shadowResourceView;
}

void SceneRenderer::PrepareDeferredBuffer()
{
    deferredBuffers->SetRenderTargets(graphics->GetContext());
    deferredBuffers->ClearRenderTargets(graphics->GetContext(), 0.0f, 0.0f, 0.0f, 1.0f);
}

void SceneRenderer::PrepareRenderShadowMap()
{
    graphics->PrepareRenderShadowMap();

    graphics->GetContext()->RSSetViewports(1, &shadowMapViewport);
    graphics->GetContext()->OMSetRenderTargets(0, nullptr, shadowDepthView);
    graphics->GetContext()->ClearDepthStencilView(shadowDepthView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void SceneRenderer::PrepareRenderSceneMap()
{
    graphics->GetContext()->OMSetRenderTargets(1, &sceneRenderTargetView, graphics->GetDepthStencilView());
    graphics->GetContext()->RSSetViewports(1, &sceneViewport);

    float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    graphics->GetContext()->ClearRenderTargetView(sceneRenderTargetView, clearColor);

    graphics->PrepareRenderSceneMap();
}

void SceneRenderer::PrepareRenderScene()
{
    graphics->GetContext()->PSSetShaderResources(DeferredBuffers::BUFFER_COUNT, 1, &shadowResourceView);
    graphics->PrepareRenderScene();
}

void SceneRenderer::RenderScene(ConstantBuffer constantBufferData, LightBuffer lightBufferData)
{
    graphics->GetOrthoWindow()->Render(deferredBuffers, constantBufferData, lightBufferData);
}

void SceneRenderer::init()
{
    initDeferredBuffers();
    initSceneMap();
    initShadowMap();
}

void SceneRenderer::initDeferredBuffers()
{
    deferredBuffers = new DeferredBuffers;
    if (!deferredBuffers)
    {
        ErrorLogger::Log(Error, "Error create new deferred buffer");
        return;
    }

    bool result = deferredBuffers->Initialize(graphics->GetDevice(),
        graphics->GetWindow()->GetScreenWidth(), graphics->GetWindow()->GetScreenHeight(),
        100, 0.1f);
    if (!result)
    {
        ErrorLogger::Log(Error, "Error initializing DeferredBuffers");
    }
}

void SceneRenderer::initSceneMap()
{
    // Creating a depth buffer
    D3D11_TEXTURE2D_DESC sceneMapDesc;
    ZeroMemory(&sceneMapDesc, sizeof(D3D11_TEXTURE2D_DESC));
    sceneMapDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    sceneMapDesc.MipLevels = 1;
    sceneMapDesc.ArraySize = 1;
    sceneMapDesc.SampleDesc.Count = 1;
    sceneMapDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    sceneMapDesc.Width = graphics->GetWindow()->GetScreenWidth();
    sceneMapDesc.Height = graphics->GetWindow()->GetScreenHeight();
    HRESULT hr = graphics->GetDevice()->CreateTexture2D(&sceneMapDesc, nullptr, &sceneMap);

    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    renderTargetViewDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    renderTargetViewDesc.Texture2D.MipSlice = 0;
    hr = graphics->GetDevice()->CreateRenderTargetView(sceneMap, &renderTargetViewDesc, &sceneRenderTargetView);

    D3D11_SHADER_RESOURCE_VIEW_DESC sceneResourceViewDesc;
    sceneResourceViewDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    sceneResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    sceneResourceViewDesc.Texture2D.MostDetailedMip = 0;
    sceneResourceViewDesc.Texture2D.MipLevels = 1;
    hr = graphics->GetDevice()->CreateShaderResourceView(sceneMap, &sceneResourceViewDesc, &sceneResourceView);

    sceneViewport = {};
    sceneViewport.Width = graphics->GetWindow()->GetScreenWidth();
    sceneViewport.Height = graphics->GetWindow()->GetScreenHeight();
    sceneViewport.TopLeftX = 0;
    sceneViewport.TopLeftY = 0;
    sceneViewport.MinDepth = 0;
    sceneViewport.MaxDepth = 1.0f;
}

void SceneRenderer::initShadowMap()
{
    // Creating a depth buffer
    D3D11_TEXTURE2D_DESC shadowMapDesc;
    ZeroMemory(&shadowMapDesc, sizeof(D3D11_TEXTURE2D_DESC));
    shadowMapDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
    shadowMapDesc.MipLevels = 1;
    shadowMapDesc.ArraySize = 1;
    shadowMapDesc.SampleDesc.Count = 1;
    shadowMapDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
    shadowMapDesc.Height = SHADOW_MAP_SIZE;
    shadowMapDesc.Width = SHADOW_MAP_SIZE;
    HRESULT hr = graphics->GetDevice()->CreateTexture2D(&shadowMapDesc, nullptr, &shadowMap);

    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;
    hr = graphics->GetDevice()->CreateDepthStencilView(shadowMap, &depthStencilViewDesc, &shadowDepthView);

    // Creating a resource view
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    shaderResourceViewDesc.Texture2D.MipLevels = 1;
    hr = graphics->GetDevice()->CreateShaderResourceView(shadowMap, &shaderResourceViewDesc, &shadowResourceView);

    // Init viewport for shadow rendering
    shadowMapViewport = {};
    ZeroMemory(&shadowMapViewport, sizeof(D3D11_VIEWPORT));
    shadowMapViewport.Height = SHADOW_MAP_SIZE;
    shadowMapViewport.Width = SHADOW_MAP_SIZE;
    shadowMapViewport.MinDepth = 0.f;
    shadowMapViewport.MaxDepth = 1.f;
}
