#include "KatamariCamera.h"

#include "Engine.h"

KatamariCamera::KatamariCamera(Engine* engine, Vector3 position, GameObject* observedObject)
    : Camera(engine, position), observedObject(observedObject), offset(position)
{
}

void KatamariCamera::Update()
{
    //Transform.setWorldPosition(observedObject->Transform->getLocalPosition() + offset);
}
