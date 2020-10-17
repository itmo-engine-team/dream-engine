#pragma once

#include <d3d11.h>
#include "SimpleMath.h"

const int BUFFERCOUNT = 2;

class DeferredBuffers
{
public:
	DeferredBuffers();
	DeferredBuffers(const DeferredBuffers&);
	~DeferredBuffers();

	bool Initialize(ID3D11Device* device, int textureWidth, int textureHeight, float screenDepth, float screenNear);
	void Shutdown();

	void SetRenderTargets(ID3D11DeviceContext* deviceContext);
	void ClearRenderTargets(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha);

	ID3D11ShaderResourceView* GetShaderResourceView(int view);

private:
	int textureWidth;
    int textureHeight;

	ID3D11Texture2D* renderTargetTextureArray[BUFFERCOUNT];
	ID3D11RenderTargetView* renderTargetViewArray[BUFFERCOUNT];
	ID3D11ShaderResourceView* shaderResourceViewArray[BUFFERCOUNT];
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilView* depthStencilView;
	D3D11_VIEWPORT viewport;
};