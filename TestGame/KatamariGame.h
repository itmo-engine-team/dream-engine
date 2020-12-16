#pragma once

#include "Game.h"
#include "SpectatorActor.h"
#include "KatamariSphere.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "StaticModelComponent.h"
#include "LightActor.h"

class KatamariGame : public Game
{
public:

    KatamariGame();
    ~KatamariGame();

    void Init(InputSystem* inputSystem, Graphics* graphics) override;
    void Update(float engineDeltaTime) override;
    void Render() override;

    CameraComponent* GetCamera() const override;
    LightComponent* GetLight() const override;

private:

    SpectatorActor* spectatorActor;
    LightActor* lightActor;

    KatamariSphere* katamariPlayer;
    StaticModelComponent* playerSphere;

    Actor* plane;
    Actor* box1;
    Actor* box2;
    Actor* box3;

    ModelData* planeModel;
    ModelData* boxModel;
    ModelData* playerModel;
    
    Texture* texture;

    void collisionCheck(GameObject* gameObject);

};
