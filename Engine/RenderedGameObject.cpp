#include <d3dcompiler.h>
#include "Game.h"
#include "Shader.h"
#include "SimpleMath.h"
#include "RenderedGameObject.h"
#include "ConstantBuffer.h"
#include <iostream>
#include <WICTextureLoader.h>
#include "LightBuffer.h"
#include "CameraBuffer.h"

using namespace DirectX::SimpleMath;

RenderedGameObject::RenderedGameObject(Game* game, Shader* shader, Vector3 position)
	: GameObject(game, position), m_shader(shader)
{

}

void RenderedGameObject::init()
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

	hr = m_game->device->CreateBuffer(
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

	hr = m_game->device->CreateBuffer(
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
	hr = m_game->device->CreateBuffer(&cbd, NULL, &pConstantBuffer);

	D3D11_BUFFER_DESC lightBufferDesc;
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	lightBufferDesc.CPUAccessFlags = 0u;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.ByteWidth = sizeof(LightBuffer);
	lightBufferDesc.StructureByteStride = 0;
	hr = m_game->device->CreateBuffer(&lightBufferDesc, NULL, &pLightBuffer);

	D3D11_BUFFER_DESC cameraBufferDesc;
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	cameraBufferDesc.CPUAccessFlags = 0u;
	cameraBufferDesc.MiscFlags = 0;
	cameraBufferDesc.ByteWidth = sizeof(CameraBuffer);
	cameraBufferDesc.StructureByteStride = 0;
	hr = m_game->device->CreateBuffer(&cameraBufferDesc, NULL, &pCameraBuffer);
}

void RenderedGameObject::update()
{
}

void RenderedGameObject::draw()
{
	m_game->context->IASetVertexBuffers(
		0u,
		1u,
		pVertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);
	m_game->context->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
	m_game->context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_shader->setShader();

	// Update Constant Buffer
	const ConstantBuffer cb =
	{
		transform->getWorldMatrix(),
		m_game->camera->getViewMatrix(),
		m_game->camera->getProjectionMatrix(),
	};
	m_game->context->UpdateSubresource(pConstantBuffer.Get(), 0, NULL, &cb, 0, 0);
	m_game->context->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

	const LightBuffer lb =
	{
		Vector4{0.15f, 0.15f, 0.15f, 1.0f},
		Vector4{1.0f, 1.0f, 1.0f, 1.0f},
		Vector3{0.0f, -1.0f, 0.0f},
		100.0f,
		{1.0f, 1.0f, 1.0f, 1.0f }
	};
	m_game->context->UpdateSubresource(pLightBuffer.Get(), 0, NULL, &lb, 0, 0);
	m_game->context->PSSetConstantBuffers(1u, 1u, pLightBuffer.GetAddressOf());

	// Update Constant Buffer
	const CameraBuffer cameraBuffer =
	{
		m_game->camera->transform.getWorldPosition(),
		0.0f
	};
	m_game->context->UpdateSubresource(pCameraBuffer.Get(), 0, NULL, &cameraBuffer, 0, 0);
	m_game->context->VSSetConstantBuffers(2u, 1u, pCameraBuffer.GetAddressOf());

	m_game->context->DrawIndexed(indicesCount, 0, 0);
}
