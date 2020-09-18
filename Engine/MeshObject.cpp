#include "MeshObject.h"
#include "Game.h"
#include <d3dcompiler.h>
#include <iostream>
#include "ConstantBuffer.h"

MeshObject::MeshObject(Game* game,
                       std::vector<Vertex>& vertices,
                       std::vector<DWORD>& indices,
					   Shader* shader) : Actor(game, shader)
{
    m_vertices = vertices;
    m_indices = indices;

    Actor::init();
}
