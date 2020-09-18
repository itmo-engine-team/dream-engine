#include "Engine/Game.h"
#include "BoxObject.h"
#include "Engine/ConstantBuffer.h"

BoxObject::BoxObject(Game* game, Shader* shader, Vector3 position, Vector4 color, Vector3 boxSize)
	: Actor(game, shader, position)
{
	m_vertices =
	{
		// Front vertices
		{
			{-boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitZ
		},
		{
			{-boxSize.x, +boxSize.y, -boxSize.z}, color, -Vector3::UnitZ
		},
		{
			{+boxSize.x, +boxSize.y, -boxSize.z}, color, -Vector3::UnitZ
		},
		{
			{+boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitZ
		},

		// Back vertices
		{
			{-boxSize.x, -boxSize.y, +boxSize.z}, color, Vector3::UnitZ
		},
		{
			{-boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitZ
		},
		{
			{+boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitZ
		},
		{
			{+boxSize.x, -boxSize.y, +boxSize.z}, color, Vector3::UnitZ
		},

		// Left vertices
		{
			{+boxSize.x, -boxSize.y, -boxSize.z}, color, Vector3::UnitX
		},
		{
			{+boxSize.x, +boxSize.y, -boxSize.z}, color, Vector3::UnitX
		},
		{
			{+boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitX
		},
		{
			{+boxSize.x, -boxSize.y, +boxSize.z}, color, Vector3::UnitX
		},

		// Right vertices
		{
			{-boxSize.x, -boxSize.y, +boxSize.z}, color, -Vector3::UnitX
		},
		{
			{-boxSize.x, +boxSize.y, +boxSize.z}, color, -Vector3::UnitX
		},
		{
			{-boxSize.x, +boxSize.y, -boxSize.z}, color, -Vector3::UnitX
		},
		{
			{-boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitX
		},

		// Top vertices
		{
			{-boxSize.x, +boxSize.y, -boxSize.z}, color, Vector3::UnitY
		},
		{
			{-boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitY
		},
		{
			{+boxSize.x, +boxSize.y, +boxSize.z}, color, Vector3::UnitY
		},
		{
			{+boxSize.x, +boxSize.y, -boxSize.z}, color, Vector3::UnitY
		},

		// Bottom vertices
		{
			{+boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitY
		},
		{
			{+boxSize.x, -boxSize.y, +boxSize.z}, color, -Vector3::UnitY
		},
		{
			{-boxSize.x, -boxSize.y, +boxSize.z}, color, -Vector3::UnitY
		},
		{
			{-boxSize.x, -boxSize.y, -boxSize.z}, color, -Vector3::UnitY
		},
	};

	m_indices =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		8, 9, 10,
		8, 10, 11,

		// right face
		12, 13, 14,
		12, 14, 15,

		// top face
		16, 17, 18,
		16, 18, 19,

		// bottom face
		20, 21, 22,
		20, 22, 23,
	};

	Actor::init();
}
