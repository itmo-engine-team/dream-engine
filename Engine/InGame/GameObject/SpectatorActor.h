#pragma once

#include "Actor.h"
#include "Component/CameraComponent.h"

class SpectatorActor : public Actor
{

public:

    SpectatorActor(Engine* engine, Transform* transform);

    CameraComponent* GetCameraComponent() const;

    void Rotate(float dx, float dy) const;
    void Translate(Vector3 translation) const;

protected:

    CameraComponent* cameraComponent = nullptr;

    float rotationSpeed = 0.1;
    float moveSpeed = 1;

    void onUpdate() override;

};
