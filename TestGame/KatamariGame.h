#pragma once

#include "Engine.h"
#include "SpectatorActor.h"
#include "KatamariSphere.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "StaticModelComponent.h"
#include "ModelShader.h"
#include "LightActor.h"

class KatamariGame : public Game
{
public:

    KatamariGame();
    ~KatamariGame();

    void Init(Engine* engine) override;
    void Update() override;
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
    ModelData* quardModel;

    ModelShader* shader;
    ModelShader* texturedShader;
    Texture* texture;
    Texture* shadowMapTexture;

    void collisionCheck(GameObject* gameObject);

};

