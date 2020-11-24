#include "DeferredBuffers.h"
#include "ErrorLogger.h"

DeferredBuffers::DeferredBuffers()
{
	for (int i = 0; i < BUFFER_COUNT; i++)
	{
		renderTargetTextureArray[i] = nullptr;
		renderTargetViewArray[i] = nullptr;
		shaderResourceViewArray[i] = nullptr;
	}

	depthStencilBuffer = nullptr;
	depthStencilView = nullptr;
}

DeferredBuffers::~DeferredBuffers()
{
}

bool DeferredBuffers::Initialize(ID3D11Device* device, int texWidth, int texHeight, float screenDepth, float screenNear)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT result;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

	// Store the width and height of the render texture.
	textureWidth = texWidth;
	textureHeight = texHeight;

	// Initialize the render target texture description.
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	// Setup the render target texture description.
	textureDesc.Width = textureWidth;
	textureDesc.Height = textureHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	// Create the render target textures.
	for (int i = 0; i < BUFFER_COUNT; i++)
	{
		result = device->CreateTexture2D(&textureDesc, NULL, &renderTargetTextureArray[i]);
		if (FAILED(result))
		{
			ErrorLogger::DirectXLog(result, Error, "Error creating RenderTargetTexture",
				__FILE__, __FUNCTION__, __LINE__);
			return false;
		}
	}

	// Setup the description of the render target view.
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target views.
	for (int i = 0; i < BUFFER_COUNT; i++)
	{
		result = device->CreateRenderTargetView(renderTargetTextureArray[i], &renderTargetViewDesc, &renderTargetViewArray[i]);
		if (FAILED(result))
		{
			ErrorLogger::DirectXLog(result, Error, "Error creating RenderTargetView",
				__FILE__, __FUNCTION__, __LINE__);
			return false;
		}
	}

	// Setup the description of the shader resource view.
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	// Create the shader resource views.
	for (int i = 0; i < BUFFER_COUNT; i++)
	{
		result = device->CreateShaderResourceView(renderTargetTextureArray[i], &shaderResourceViewDesc, &shaderResourceViewArray[i]);
		if (FAILED(result))
		{
			ErrorLogger::DirectXLog(result, Error, "Error creating ShaderResourceView",
				__FILE__, __FUNCTION__, __LINE__);
			return false;
		}
	}

	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = textureWidth;
	depthBufferDesc.Height = textureHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	result = device->CreateTexture2D(&depthBufferDesc, NULL, &depthStencilBuffer);
	if (FAILED(result))
	{
		ErrorLogger::DirectXLog(result, Error, "Error creating DepthStencilBuffer",
			__FILE__, __FUNCTION__, __LINE__);
		return false;
	}

	// Initailze the depth stencil view description.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	result = device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &depthStencilView);
	if (FAILED(result))
	{
		ErrorLogger::DirectXLog(result, Error, "Error creating DepthStencilView",
			__FILE__, __FUNCTION__, __LINE__);
		return false;
	}

	// Setup the viewport for rendering.
	viewport.Width = static_cast<float>(textureWidth);
	viewport.Height = static_cast<float>(textureHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	return true;
}

void DeferredBuffers::Shutdown()
{
	if (depthStencilView)
	{
		depthStencilView->Release();
		depthStencilView = nullptr;
	}

	if (depthStencilBuffer)
	{
		depthStencilBuffer->Release();
		depthStencilBuffer = nullptr;
	}

	for (int i = 0; i < BUFFER_COUNT; i++)
	{
		if (shaderResourceViewArray[i])
		{
			shaderResourceViewArray[i]->Release();
			shaderResourceViewArray[i] = nullptr;
		}

		if (renderTargetViewArray[i])
		{
			renderTargetViewArray[i]->Release();
			renderTargetViewArray[i] = nullptr;
		}

		if (renderTargetTextureArray[i])
		{
			renderTargetTextureArray[i]->Release();
			renderTargetTextureArray[i] = nullptr;
		}
	}
}

void DeferredBuffers::SetRenderTargets(ID3D11DeviceContext* deviceContext)
{
	// Bind the render target view array and depth stencil buffer to the output render pipeline.
	deviceContext->OMSetRenderTargets(BUFFER_COUNT, renderTargetViewArray, depthStencilView);

	// Set the viewport.
	deviceContext->RSSetViewports(1, &viewport);
}


void DeferredBuffers::ClearRenderTargets(ID3D11DeviceContext* deviceContext, float red, float green, float blue, float alpha)
{
	float color[4];

	// Setup the color to clear the buffer to.
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	// Clear the render target buffers.
	for (int i = 0; i < BUFFER_COUNT; i++)
	{
		deviceContext->ClearRenderTargetView(renderTargetViewArray[i], color);
	}

	// Clear the depth buffer.
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

ID3D11ShaderResourceView* DeferredBuffers::GetShaderResourceView(int view) const
{
	return shaderResourceViewArray[view];
}

ID3D11ShaderResourceView* const* DeferredBuffers::GetShaderResourceViewArray() const
{
	return shaderResourceViewArray;
}
