#pragma once

#include "GameComponent/Camera.h"
#include "GameObject/GameObject.h"

class KatamariCamera : public Camera
{
public:

    KatamariCamera(Engine* engine, Vector3 position, GameObject* observedObject);
    void Update() override;

private:

    Vector3 offset;
    GameObject* observedObject;

};

