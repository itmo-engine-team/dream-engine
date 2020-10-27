#include "LightShader.h"

#include <d3dcompiler.h>

#include "ErrorLogger.h"


LightShader::LightShader(Graphics* graphics, const wchar_t* shaderPath, Texture* texture) : TexturedShader(graphics, shaderPath, texture)
{
	vertexShader = 0;
	pixelShader = 0;
	layout = 0;
	sampleState = 0;
	matrixBuffer = 0;
	lightBuffer = 0;
}

LightShader::~LightShader()
{
}


bool LightShader::Initialize()
{
	bool result;

	ID3D11Device* device = graphics->GetDevice();

	// Initialize the vertex and pixel shaders.
	result = InitializeShader(device, shaderPath.c_str());
	if (!result)
	{
		return false;
	}

	return true;
}


void LightShader::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}


bool LightShader::Render(ID3D11DeviceContext* deviceContext, int indexCount,  ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture,
	Vector3 lightDirection)
{
	bool result;


	// Set the shader parameters that it will use for rendering.
	result = SetShaderParameters(deviceContext, colorTexture, normalTexture, lightDirection);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, indexCount);

	return true;
}


bool LightShader::InitializeShader(ID3D11Device* device, const wchar_t* fxFileName)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC lightBufferDesc;
	std::wstring shaderPath = std::wstring(fxFileName);

	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	//// Compile the vertex shader code.
	//result = D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
	//	&vertexShaderBuffer, &errorMessage);
	//if (FAILED(result))
	//{
	//	// If the shader failed to compile it should have writen something to the error message.
	//	if (errorMessage) {
	//		char* compileErrors = static_cast<char*>(errorMessage->GetBufferPointer());
	//		ErrorLogger::DirectXLog(result, Error, compileErrors, __FILE__, __FUNCTION__, __LINE__);
	//	}
	//	// If there was nothing in the error message then it simply could not find the shader file itself.
	//	else
	//	{
	//		ErrorLogger::DirectXLog(result, Error, "Missing Shader file", __FILE__, __FUNCTION__, __LINE__);
	//	}

	//	return false;
	//}

	//// Compile the pixel shader code.
	//result = D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
	//	&vertexShaderBuffer, &errorMessage);
	//if (FAILED(result))
	//{
	//	// If the shader failed to compile it should have writen something to the error message.
	//	if (errorMessage) {
	//		char* compileErrors = static_cast<char*>(errorMessage->GetBufferPointer());
	//		ErrorLogger::DirectXLog(result, Error, compileErrors, __FILE__, __FUNCTION__, __LINE__);
	//	}
	//	// If there was nothing in the error message then it simply could not find the file itself.
	//	else
	//	{
	//		ErrorLogger::DirectXLog(result, Error, "Missing Shader file", __FILE__, __FUNCTION__, __LINE__);
	//	}

	//	return false;
	//}

	// Create the vertex shader from the buffer.
	//result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);
	//if (FAILED(result))
	//{
	//	return false;
	//}

	//// Create the pixel shader from the buffer.
	//result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);
	//if (FAILED(result))
	//{
	//	return false;
	//}


    //// Create the vertex input layout description.
    //polygonLayout[0].SemanticName = "POSITION";
    //polygonLayout[0].SemanticIndex = 0;
    //polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    //polygonLayout[0].InputSlot = 0;
    //polygonLayout[0].AlignedByteOffset = 0;
    //polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    //polygonLayout[0].InstanceDataStepRate = 0;

    //polygonLayout[1].SemanticName = "TEXCOORD";
    //polygonLayout[1].SemanticIndex = 0;
    //polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
    //polygonLayout[1].InputSlot = 0;
    //polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    //polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    //polygonLayout[1].InstanceDataStepRate = 0;

    //// Get a count of the elements in the layout.
    //numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

    //// Create the vertex input layout.
    //result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(),
	   // &layout);
    //if (FAILED(result))
    //{
	   // return false;
    //}

    // Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
   /* vertexShaderBuffer->Release();
    vertexShaderBuffer = 0;

    pixelShaderBuffer->Release();
    pixelShaderBuffer = 0;*/


    //// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
    //matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    //matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
    //matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    //matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    //matrixBufferDesc.MiscFlags = 0;
    //matrixBufferDesc.StructureByteStride = 0;

    //// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
    //result = device->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);
    //if (FAILED(result))
    //{
	   // return false;
    //}

    // Setup the description of the light dynamic constant buffer that is in the pixel shader.
    lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    lightBufferDesc.ByteWidth = sizeof(LightBufferType);
    lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    lightBufferDesc.MiscFlags = 0;
    lightBufferDesc.StructureByteStride = 0;

    // Create the constant buffer pointer so we can access the pixel shader constant buffer from within this class.
    result = device->CreateBuffer(&lightBufferDesc, NULL, &lightBuffer);
    if (FAILED(result))
    {
	    return false;
    }

    return true;
}

void LightShader::ShutdownShader()
{
	// Release the light constant buffer.
	if (lightBuffer)
	{
		lightBuffer->Release();
		lightBuffer = 0;
	}

	// Release the matrix constant buffer.
	if (matrixBuffer)
	{
		matrixBuffer->Release();
		matrixBuffer = 0;
	}

	// Release the sampler state.
	if (sampleState)
	{
		sampleState->Release();
		sampleState = 0;
	}

	// Release the layout.
	if (layout)
	{
		layout->Release();
		layout = 0;
	}

	// Release the pixel shader.
	if (pixelShader)
	{
		pixelShader->Release();
		pixelShader = 0;
	}

	// Release the vertex shader.
	if (vertexShader)
	{
		vertexShader->Release();
		vertexShader = 0;
	}
}

bool LightShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* colorTexture,
	ID3D11ShaderResourceView* normalTexture, Vector3 lightDirection)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;
	MatrixBufferType* dataPtr;
	LightBufferType* dataPtr2;


	//// Transpose the matrices to prepare them for the shader.
	//worldMatrix.Transpose(worldMatrix);
	//viewMatrix.Transpose(viewMatrix);
	//projectionMatrix.Transpose(projectionMatrix);

	//// Lock the constant buffer so it can be written to.
	//result = deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	//if (FAILED(result))
	//{
	//	return false;
	//}

	//// Get a pointer to the data in the constant buffer.
	//dataPtr = static_cast<MatrixBufferType*>(mappedResource.pData);

	//// Copy the matrices into the constant buffer.
	//dataPtr->world = worldMatrix;
	//dataPtr->view = viewMatrix;
	//dataPtr->projection = projectionMatrix;

	//// Unlock the constant buffer.
	//deviceContext->Unmap(matrixBuffer, 0);

	//// Set the position of the constant buffer in the vertex shader.
	//bufferNumber = 0;

	//// Now set the constant buffer in the vertex shader with the updated values.
	//deviceContext->VSSetConstantBuffers(bufferNumber, 1, &matrixBuffer);
	//// Set shader texture resources in the pixel shader.
	//deviceContext->PSSetShaderResources(0, 1, &colorTexture);
	//deviceContext->PSSetShaderResources(1, 1, &normalTexture);

	// Lock the light constant buffer so it can be written to.
	result = deviceContext->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr2 = static_cast<LightBufferType*>(mappedResource.pData);

	// Copy the lighting variables into the constant buffer.
	dataPtr2->lightDirection = lightDirection;
	dataPtr2->padding = 0.0f;

	// Unlock the constant buffer.
	deviceContext->Unmap(lightBuffer, 0);

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &lightBuffer);

	return true;
}


void LightShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(layout);

	// Set the vertex and pixel shaders that will be used to render.
	deviceContext->VSSetShader(vertexShader, NULL, 0);
	deviceContext->PSSetShader(pixelShader, NULL, 0);

	// Set the sampler state in the pixel shader.
	deviceContext->PSSetSamplers(0, 1, &sampleState);

	// Render the geometry.
	deviceContext->DrawIndexed(indexCount, 0, 0);
}
