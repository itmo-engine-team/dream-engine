#pragma once
#include "GameObject.h"
#include "MeshObject.h"

class ModelObject : public GameObject
{
public:

	ModelObject(Game* game, const std::string& filePath, Shader* shader);

	void init() override;
	void update() override;
	void draw() override;
	void addMesh(MeshObject* mesh);
	
protected:
	
	std::vector<MeshObject*> meshes;
	Shader* m_shader;
	
};

