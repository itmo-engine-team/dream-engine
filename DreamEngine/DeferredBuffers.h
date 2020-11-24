#pragma once

#include <d3d11.h>

class DeferredBuffers
{

public:

	DeferredBuffers();
	~DeferredBuffers();

	bool Initialize(ID3D11Device* device, int texWidth, int texHeight,
		float screenDepth, float screenNear);
	void Shutdown();

	void SetRenderTargets(ID3D11DeviceContext* deviceContext);
	void ClearRenderTargets(ID3D11DeviceContext* deviceContext,
		float red, float green, float blue, float alpha);

	ID3D11ShaderResourceView* GetShaderResourceView(int view) const;

private:

	static const int BUFFER_COUNT = 2;

	int textureWidth, textureHeight;

	ID3D11Texture2D* renderTargetTextureArray[BUFFER_COUNT];
	ID3D11RenderTargetView* renderTargetViewArray[BUFFER_COUNT];
	ID3D11ShaderResourceView* shaderResourceViewArray[BUFFER_COUNT];
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilView* depthStencilView;
	D3D11_VIEWPORT viewport;

};