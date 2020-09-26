#include "KatamariSphere.h"
#include <iostream>

KatamariSphere::KatamariSphere(Engine* engine, Transform* transform)
: Actor(engine, transform)
{
	collider = new DirectX::BoundingSphere({ 0, 0, 0 }, 0.7);
}

void KatamariSphere::onUpdate()
{
	Vector3 worldPos = transform->GetWorldPosition();
	collider->Center = worldPos;
}


