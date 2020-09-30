#pragma once

#include "GameComponent/Camera.h"
#include "GameObject/GameObject.h"

class KatamariCamera : public Camera
{
public:

    KatamariCamera(Engine* engine, Vector3 position, GameObject* observedObject);
    void update() override;

private:

    Vector3 m_offset;
    GameObject* m_observedObject;

};

