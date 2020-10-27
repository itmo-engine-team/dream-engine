//#include "DeferredShader.h"
//
//#include <d3dcompiler.h>
//#include "ErrorLogger.h"
//
//DeferredShader::DeferredShader(Graphics* graphics, const wchar_t* shaderPath, Texture* texture) : graphics(graphics), shaderPath(std::wstring(shaderPath), texture(texture))
//{
//}
//
//DeferredShader::~DeferredShader()
//{
//}
//
//bool DeferredShader::Initialize()
//{
//	bool result;
//	ID3D11Device* device = graphics->GetDevice();
//
//	// Initialize the vertex and pixel shaders.
//	result = InitializeShader(device);
//	if (!result)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//void DeferredShader::Shutdown()
//{
//	// Shutdown the vertex and pixel shaders as well as the related objects.
//	ShutdownShader();
//
//}
//
//bool DeferredShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, Matrix worldMatrix, Matrix viewMatrix, Matrix projectionMatrix, ID3D11ShaderResourceView* texture)
//{
//	bool result;
//
//	// Set the shader parameters that it will use for rendering.
//	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture);
//	if (!result)
//	{
//		return false;
//	}
//
//	// Now render the prepared buffers with the shader.
//	RenderShader(deviceContext, indexCount);
//
//	return true;
//}
//
//bool DeferredShader::InitializeShader(ID3D11Device* device)
//{
//	HRESULT result;
//	ID3D10Blob* errorMessage;
//	ID3D10Blob* vertexShaderBuffer;
//	ID3D10Blob* pixelShaderBuffer;
//	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
//	unsigned int numElements;
//	D3D11_SAMPLER_DESC samplerDesc;
//	D3D11_BUFFER_DESC matrixBufferDesc;
//	//std::wstring shaderPath = std::wstring(fxFileName);
//
//	// Initialize the pointers this function will use to null.
//	errorMessage = 0;
//	vertexShaderBuffer = 0;
//	pixelShaderBuffer = 0;
//
//	// Compile the vertex shader code.
//	result = D3DCompileFromFile(shaderPath.c_str(),
//		nullptr,
//		nullptr,
//		"VSMain",
//		"vs_5_0",
//		D3D10_SHADER_ENABLE_STRICTNESS,
//		0,
//		&vertexShaderBuffer,
//		&errorMessage);
//
//	if (FAILED(result))
//	{
//		// If the shader failed to compile it should have writen something to the error message.
//		if (errorMessage) {
//			char* compileErrors = static_cast<char*>(errorMessage->GetBufferPointer());
//			ErrorLogger::DirectXLog(result, Error, compileErrors, __FILE__, __FUNCTION__, __LINE__);
//		}
//		// If there was nothing in the error message then it simply could not find the shader file itself.
//		else
//		{
//			ErrorLogger::DirectXLog(result, Error, "Missing Shader file", __FILE__, __FUNCTION__, __LINE__);
//		}
//		return false;
//	}
//
//	// Compile the pixel shader code.
//	result = D3DCompileFromFile(shaderPath.c_str(),
//		nullptr, nullptr ,
//		"PSMain", "ps_5_0",
//		D3D10_SHADER_ENABLE_STRICTNESS,
//		0, &pixelShaderBuffer, &errorMessage);
//
//	if (FAILED(result))
//	{
//		// If the shader failed to compile it should have writen something to the error message.
//		if (errorMessage) {
//			char* compileErrors = static_cast<char*>(errorMessage->GetBufferPointer());
//			ErrorLogger::DirectXLog(result, Error, compileErrors, __FILE__, __FUNCTION__, __LINE__);
//		}
//		// If there was nothing in the error message then it simply could not find the shader file itself.
//		else
//		{
//			ErrorLogger::DirectXLog(result, Error, "Missing Shader file", __FILE__, __FUNCTION__, __LINE__);
//		}
//		return false;
//	}
//
//	// Create the vertex shader from the buffer.
//	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);
//	if (FAILED(result))
//	{
//		return false;
//	}
//
//	// Create the pixel shader from the buffer.
//	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);
//	if (FAILED(result))
//	{
//		return false;
//	}
//
//	// Create the vertex input layout description.
//	polygonLayout[0].SemanticName = "POSITION";
//	polygonLayout[0].SemanticIndex = 0;
//	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
//	polygonLayout[0].InputSlot = 0;
//	polygonLayout[0].AlignedByteOffset = 0;
//	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
//	polygonLayout[0].InstanceDataStepRate = 0;
//
//	polygonLayout[1].SemanticName = "TEXCOORD";
//	polygonLayout[1].SemanticIndex = 0;
//	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
//	polygonLayout[1].InputSlot = 0;
//	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
//	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
//	polygonLayout[1].InstanceDataStepRate = 0;
//
//	polygonLayout[2].SemanticName = "NORMAL";
//	polygonLayout[2].SemanticIndex = 0;
//	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
//	polygonLayout[2].InputSlot = 0;
//	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
//	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
//	polygonLayout[2].InstanceDataStepRate = 0;
//
//	// Get a count of the elements in the layout.
//	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);
//
//	// Create the vertex input layout.
//	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(),
//		&layout);
//	if (FAILED(result))
//	{
//		return false;
//	}
//
//	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
//	vertexShaderBuffer->Release();
//	vertexShaderBuffer = 0;
//
//	pixelShaderBuffer->Release();
//	pixelShaderBuffer = 0;
//
//	return true;
//}
//
//void DeferredShader::ShutdownShader()
//{
//	// Release the matrix constant buffer.
//	if (matrixBuffer)
//	{
//		matrixBuffer->Release();
//		matrixBuffer = 0;
//	}
//
//	// Release the sampler state.
//	if (sampleStateWrap)
//	{
//		sampleStateWrap->Release();
//		sampleStateWrap = 0;
//	}
//
//	// Release the layout.
//	if (layout)
//	{
//		layout->Release();
//		layout = 0;
//	}
//
//	// Release the pixel shader.
//	if (pixelShader)
//	{
//		pixelShader->Release();
//		pixelShader = 0;
//	}
//
//	// Release the vertex shader.
//	if (vertexShader)
//	{
//		vertexShader->Release();
//		vertexShader = 0;
//	}
//}
//
//void DeferredShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
//{
//	// Set the vertex input layout.
//	deviceContext->IASetInputLayout(layout);
//
//	// Set the vertex and pixel shaders that will be used to render.
//	deviceContext->VSSetShader(vertexShader, NULL, 0);
//	deviceContext->PSSetShader(pixelShader, NULL, 0);
//
//	// Set the sampler states in the pixel shader.
//	deviceContext->PSSetSamplers(0, 1, &sampleStateWrap);
//
//	// Render the geometry.
//	deviceContext->DrawIndexed(indexCount, 0, 0);
//
//}
