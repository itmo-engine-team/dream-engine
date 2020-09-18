#include "Engine/Game.h"
#include "PyramidObject.h"
#include "Engine/ConstantBuffer.h"

using namespace DirectX;

PyramidObject::PyramidObject(Game* game, Shader* shader, Vector3 position, Vector4 color)
: Actor(game, shader, position)
{

	// Создание буфера вершин (пять углов пирамиды)
	m_vertices =
	{
		/* координаты X, Y, Z				цвет R, G, B, A					 */
		/*{XMFLOAT3(0.0f, 1.5f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3(-1.0f, 0.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3(1.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(-1.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(1.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)}*/
	};

	// Создание буфера индексов:
	// Создание массива с данными
	m_indices =
	{
		// индексы массива vertices[], по которым строятся треугольники
		0, 2, 1, /* Треугольник 1 = vertices[0], vertices[2], vertices[3] */
		0, 3, 4, /* Треугольник 2 = vertices[0], vertices[3], vertices[4] */
		0, 1, 3, /* и т. д. */
		0, 4, 2,
		1, 2, 3,
		2, 4, 3,
	};

	Actor::init();
}

void PyramidObject::preDraw()
{
	m_rotateDelta += static_cast<float>(DirectX::XM_PI) * pGame->deltaTime;
	
	const ConstantBuffer cb =
	{
		{
			Matrix::CreateRotationY(m_rotateDelta).Transpose()
		},
		pGame->camera->getViewMatrix().Transpose(),
		pGame->camera->getProjectionMatrix(),
	};
	pGame->context->UpdateSubresource(pConstantBuffer.Get(), 0, NULL, &cb, 0, 0);
}
