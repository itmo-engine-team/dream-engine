#include "KatamariCamera.h"

#include "Engine.h"

KatamariCamera::KatamariCamera(Engine* engine, Vector3 position, GameObject* observedObject)
    : Camera(engine, position), m_observedObject(observedObject), m_offset(position)
{
}

void KatamariCamera::update()
{
    //transform.setWorldPosition(m_observedObject->transform->getLocalPosition() + m_offset);
}
