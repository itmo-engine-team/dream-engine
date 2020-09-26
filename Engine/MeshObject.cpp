#include "MeshObject.h"

#include <d3dcompiler.h>

#include "Engine.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "LightBuffer.h"
#include "CameraBuffer.h"

MeshObject::MeshObject(Engine* engine, Transform* transform, MeshData* meshData, Shader* shader)
: engine(engine), transform(transform), meshData(meshData), shader(shader)
{
	graphics = engine->GetGraphics();

	HRESULT hr;

	// Create Vertex Buffer
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = meshData->GetVertices().size() * sizeof(Vertex);
	bd.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = meshData->GetVertices().data();

	hr = graphics->GetDevice()->CreateBuffer(
		&bd,
		&sd,
		pVertexBuffer.GetAddressOf()
		);

	stride = sizeof(Vertex);

	// Create Index buffer
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = meshData->GetIndices().size() * sizeof(DWORD);
	ibd.StructureByteStride = sizeof(DWORD);

	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = meshData->GetIndices().data();

	hr = graphics->GetDevice()->CreateBuffer(
		&ibd,
		&isd,
		pIndexBuffer.GetAddressOf()
		);

	CD3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0u;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(ConstantBuffer);
	cbd.StructureByteStride = 0u;
	hr = graphics->GetDevice()->CreateBuffer(&cbd, NULL, &pConstantBuffer);

	D3D11_BUFFER_DESC lightBufferDesc;
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	lightBufferDesc.CPUAccessFlags = 0u;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.ByteWidth = sizeof(LightBuffer);
	lightBufferDesc.StructureByteStride = 0;
	hr = graphics->GetDevice()->CreateBuffer(&lightBufferDesc, NULL, &pLightBuffer);

	D3D11_BUFFER_DESC cameraBufferDesc;
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	cameraBufferDesc.CPUAccessFlags = 0u;
	cameraBufferDesc.MiscFlags = 0;
	cameraBufferDesc.ByteWidth = sizeof(CameraBuffer);
	cameraBufferDesc.StructureByteStride = 0;
	hr = graphics->GetDevice()->CreateBuffer(&cameraBufferDesc, NULL, &pCameraBuffer);
}

void MeshObject::Draw()
{
	graphics->GetContext()->IASetVertexBuffers(
		0u,
		1u,
		pVertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);
	graphics->GetContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
	graphics->GetContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->SetShader();

	// Update Constant Buffer
	const ConstantBuffer cb =
	{
		transform->GetWorldMatrix(),
		engine->GetCamera()->getViewMatrix(),
		engine->GetCamera()->getProjectionMatrix(),
	};
	graphics->GetContext()->UpdateSubresource(pConstantBuffer.Get(), 0, NULL, &cb, 0, 0);
	graphics->GetContext()->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

	const LightBuffer lb =
	{
		Vector4{0.15f, 0.15f, 0.15f, 1.0f},
		Vector4{1.0f, 1.0f, 1.0f, 1.0f},
		Vector3{0.0f, -1.0f, 0.0f},
		100.0f,
		{1.0f, 1.0f, 1.0f, 1.0f }
	};
	graphics->GetContext()->UpdateSubresource(pLightBuffer.Get(), 0, NULL, &lb, 0, 0);
	graphics->GetContext()->PSSetConstantBuffers(1u, 1u, pLightBuffer.GetAddressOf());

	// Update Constant Buffer
	const CameraBuffer cameraBuffer =
	{
		engine->GetCamera()->transform.GetWorldPosition(),
		0.0f
	};

	graphics->GetContext()->UpdateSubresource(pCameraBuffer.Get(), 0, NULL, &cameraBuffer, 0, 0);
	graphics->GetContext()->VSSetConstantBuffers(2u, 1u, pCameraBuffer.GetAddressOf());

	graphics->GetContext()->DrawIndexed(meshData->GetIndicesCount(), 0, 0);
}
