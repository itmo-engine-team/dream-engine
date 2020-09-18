#include "Game.h"
#include "ModelObject.h"
#include <WICTextureLoader.h>

ModelObject::ModelObject(Game* game, const std::string& filePath, Shader* shader) : GameObject(game), m_shader(shader)
{
	pGame->meshRenderer->addModel(this, filePath, shader);
	
	ModelObject::init();
}

void ModelObject::init()
{
}

void ModelObject::update()
{
}

void ModelObject::draw()
{
	for (MeshObject* meshObject : meshes)
	{
		meshObject->draw();
	}
}

void ModelObject::addMesh(MeshObject* mesh)
{
	meshes.push_back(mesh);
	mesh->pTransform->SetParent(transform);
}
