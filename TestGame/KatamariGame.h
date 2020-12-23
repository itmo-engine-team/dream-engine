#pragma once

#include "Game.h"
#include "A_Spectator.h"
#include "KatamariSphere.h"
#include "ACS_Camera.h"
#include "ACS_Light.h"
#include "ACS_StaticModel.h"
#include "A_Light.h"

class KatamariGame
{
public:

    KatamariGame();
    ~KatamariGame();

    /*void Init(InputSystem* inputSystem, Graphics* graphics) override;
    void Update(float engineDeltaTime) override;
    void Render() override;*/

    /*ACS_Camera* GetCamera() const override;
    ACS_Light* GetLight() const override;*/

private:

    A_Spectator* spectatorActor;
    A_Light* lightActor;

    KatamariSphere* katamariPlayer;
    ACS_StaticModel* playerSphere;

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
