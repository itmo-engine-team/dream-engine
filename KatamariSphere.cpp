#include "KatamariSphere.h"
#include <iostream>

KatamariSphere::KatamariSphere(Game* game, const std::string& filePath, Shader* shader)
  : ModelObject(game, filePath, shader)
{
	collider = new DirectX::BoundingSphere({ 0, 0, 0 }, 0.7);
}

void KatamariSphere::update()
{
	Vector3 worldPos = transform->getWorldPosition();
	collider->Center = worldPos;
	//std::cout << collider->Center.x << " " << collider->Center.y << " " << collider->Center.z << std::endl;
}
