#pragma once

#include "Actor.h"
#include "ACS_Camera.h"

class A_Spectator : public Actor
{

public:

    A_Spectator(ActorContext context, Transform* transform);

    ACS_Camera* GetCameraComponent() const;

    void Rotate(float dx, float dy) const;
    void Translate(Vector3 translation) const;

protected:

    ACS_Camera* cameraComponent = nullptr;

    float rotationSpeed = 0.1;
    float moveSpeed = 1;

    void onUpdate() override;

};
