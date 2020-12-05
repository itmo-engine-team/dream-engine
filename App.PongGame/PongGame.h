#pragma once

#include "Engine.h"
#include "SpectatorActor.h"
#include "Ball.h"
#include "Player.h"
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

    Ball* ball;
    StaticModelComponent* ballSphere;

    Player* player1;
    Player* player2;

    Actor* plane;
    Actor* wall1;
    Actor* wall2;

    ModelData* planeModel;
    ModelData* wallModel;
    ModelData* playerModel;
    ModelData* ballModel;
    
    Texture* texture;

    void collisionCheck(GameObject* gameObject);

};
