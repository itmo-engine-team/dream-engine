#pragma once

#include "Engine.h"
#include "SpectatorActor.h"
#include "Ball.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "StaticModelComponent.h"
#include "LightActor.h"

class PongGame : public Game
{
public:

    PongGame();
    ~PongGame();

    void Init(Engine* engine) override;
    void Update() override;
    void Render() override;

    CameraComponent* GetCamera() const override;
    LightComponent* GetLight() const override;

private:

    SpectatorActor* spectatorActor;
    LightActor* lightActor;

    Ball* katamariPlayer;
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
