#include "Game.h"
#include "Texture.h"
#include <WICTextureLoader.h>

Texture::Texture(Game* game, const wchar_t* texturePath) : m_game(game)
{
	// Загрузка текстуры из файла
	auto hr = DirectX::CreateWICTextureFromFile(m_game->graphics->device, texturePath, nullptr, &g_pTextureRV, 0);
	
	// Создание сэмпла (описания) текстуры
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;      // Тип фильтрации
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;         // Задаем координаты
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Создаем интерфейс сэмпла текстурирования
	hr = m_game->graphics->device->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
}

void Texture::setTexture()
{
	m_game->graphics->context->PSSetShaderResources(0, 1, &g_pTextureRV);
	m_game->graphics->context->PSSetSamplers(0, 1, &g_pSamplerLinear);
}
