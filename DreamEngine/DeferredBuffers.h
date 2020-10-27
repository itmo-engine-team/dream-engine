//#pragma once
//
//#include <d3d11.h>
//
//#include "Graphics.h"
//
//const int BUFFERCOUNT = 2;
//
//class DeferredBuffers
//{
//public:
//	DeferredBuffers(Graphics* graphics);
//	~DeferredBuffers();
//
//	bool Initialize(int texWidth, int texHeight);
//	void Shutdown();
//
//	void SetRenderTargets(ID3D11DeviceContext* deviceContext);
//	void ClearRenderTargets(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha);
//
//	ID3D11ShaderResourceView* GetShaderResourceView(int view);
//
//private:
//	int textureWidth;
//    int textureHeight;
//
//	ID3D11Texture2D* renderTargetTextureArray[BUFFERCOUNT];
//	ID3D11RenderTargetView* renderTargetViewArray[BUFFERCOUNT];
//	ID3D11ShaderResourceView* shaderResourceViewArray[BUFFERCOUNT];
//	ID3D11Texture2D* depthStencilBuffer;
//	ID3D11DepthStencilView* depthStencilView;
//	D3D11_VIEWPORT viewport;
//
//protected:
//	Graphics* graphics = nullptr;
//};