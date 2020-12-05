#pragma once

#include "Engine.h"
#include "SpectatorActor.h"
#include "Ball.h"
#include "Player.h"
#include "Wall.h"
#include "Gate.h"
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
    void Render2D() override;

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
    Wall* wall1;
    Wall* wall2;
    Gate* gate1;
    Gate* gate2;

    Actor* lastHittedActor;

    ModelData* planeModel;
    ModelData* wallModel;
    ModelData* gateModel;
    ModelData* playerModel;
    ModelData* ballModel;

    int player1Score = 0;
    int player2Score = 0;
    
    Texture* texture;

    void collisionCheck();
    void resetBall();
    void generateNewDirectionZ(float directionDelta);
    void generateNewDirectionX(float directionDelta);
};
