#include <d3dcompiler.h>
#include "Game.h"
#include "Shader.h"
#include "SimpleMath.h"
#include "Actor.h"
#include "ConstantBuffer.h"
#include <iostream>
#include <WICTextureLoader.h>
#include "LightBuffer.h"
#include "CameraBuffer.h"

using namespace DirectX::SimpleMath;

Actor::Actor(Game* game, Shader* shader, Transform* transform)
	: GameObject(game), pTransform(transform), m_shader(shader)
{

}

void Actor::init()
{
	indicesCount = std::size(m_indices);

	HRESULT hr;

	// Create Vertex Buffer
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = m_vertices.size() * sizeof(Vertex);
	bd.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = m_vertices.data();

	hr = pGame->device->CreateBuffer(
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
	ibd.ByteWidth = m_indices.size() * sizeof(DWORD);
	ibd.StructureByteStride = sizeof(DWORD);

	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = m_indices.data();

	hr = pGame->device->CreateBuffer(
		&ibd,
		&isd,
		pIndexBuffer.GetAddressOf()
		);
	indicesCount = std::size(m_indices);

	CD3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0u;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(ConstantBuffer);
	cbd.StructureByteStride = 0u;
	hr = pGame->device->CreateBuffer(&cbd, NULL, &pConstantBuffer);

	D3D11_BUFFER_DESC lightBufferDesc;
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	lightBufferDesc.CPUAccessFlags = 0u;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.ByteWidth = sizeof(LightBuffer);
	lightBufferDesc.StructureByteStride = 0;
	hr = pGame->device->CreateBuffer(&lightBufferDesc, NULL, &pLightBuffer);

	D3D11_BUFFER_DESC cameraBufferDesc;
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	cameraBufferDesc.CPUAccessFlags = 0u;
	cameraBufferDesc.MiscFlags = 0;
	cameraBufferDesc.ByteWidth = sizeof(CameraBuffer);
	cameraBufferDesc.StructureByteStride = 0;
	hr = pGame->device->CreateBuffer(&cameraBufferDesc, NULL, &pCameraBuffer);
}

void Actor::update()
{
}

void Actor::draw()
{
	pGame->context->IASetVertexBuffers(
		0u,
		1u,
		pVertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);
	pGame->context->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
	pGame->context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_shader->setShader();

	// Update Constant Buffer
	const ConstantBuffer cb =
	{
		pTransform->GetWorldMatrix(),
		pGame->camera->getViewMatrix(),
		pGame->camera->getProjectionMatrix(),
	};
	pGame->context->UpdateSubresource(pConstantBuffer.Get(), 0, NULL, &cb, 0, 0);
	pGame->context->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

	const LightBuffer lb =
	{
		Vector4{0.15f, 0.15f, 0.15f, 1.0f},
		Vector4{1.0f, 1.0f, 1.0f, 1.0f},
		Vector3{0.0f, -1.0f, 0.0f},
		100.0f,
		{1.0f, 1.0f, 1.0f, 1.0f }
	};
	pGame->context->UpdateSubresource(pLightBuffer.Get(), 0, NULL, &lb, 0, 0);
	pGame->context->PSSetConstantBuffers(1u, 1u, pLightBuffer.GetAddressOf());

	// Update Constant Buffer
	const CameraBuffer cameraBuffer =
	{
		pGame->camera->transform.GetWorldPosition(),
		0.0f
	};
	pGame->context->UpdateSubresource(pCameraBuffer.Get(), 0, NULL, &cameraBuffer, 0, 0);
	pGame->context->VSSetConstantBuffers(2u, 1u, pCameraBuffer.GetAddressOf());

	pGame->context->DrawIndexed(indicesCount, 0, 0);
}

Transform* Actor::GetTransform() const
{
	return pTransform;
}
