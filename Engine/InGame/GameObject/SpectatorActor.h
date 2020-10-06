#pragma once
#include "Actor.h"
#include "Component/CameraComponent.h"

class SpectatorActor : public Actor
{

public:

    SpectatorActor(Engine* engine, Transform* transform);

    CameraComponent* GetCameraComponent() const;

    void onUpdate() override;

    void Rotate(float dx, float dy) const;
    void Translate(Vector3 translation) const;

private:

    CameraComponent* cameraComponent = nullptr;

    float rotationSpeed = 0.1;
    float moveSpeed = 1;

};

