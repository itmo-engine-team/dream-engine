#pragma once

#include <d3d11_1.h>
#include <vector>

#include "RenderedGameObject.h"

class Game;
using namespace Microsoft::WRL;

class MeshObject : public RenderedGameObject
{
public:
	MeshObject(Game* game,
		std::vector<Vertex>& vertices,
		std::vector<DWORD>& indices,
		Shader* shader);

};

