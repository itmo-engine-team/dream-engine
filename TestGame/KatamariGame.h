#pragma once

#include "Engine.h"
#include "SpectatorActor.h"
#include "KatamariSphere.h"
#include "CameraComponent.h"
#include "LightComponent.h"
#include "StaticModelComponent.h"
#include "TexturedShader.h"
#include "LightActor.h"
#include "LightShader.h"

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
    LightShader* lightShader;

    KatamariSphere* katamariPlayer;
    StaticModelComponent* playerSphere;

    Actor* plane;
    Actor* box1;
    Actor* box2;
    Actor* box3;
    Actor* quard;

    ModelData* planeModel;
    ModelData* boxModel;
    ModelData* playerModel;
    ModelData* quardModel;

    Shader* shader;
    TexturedShader* texturedShader;
    TexturedShader* texturedShadowShader;
    Texture* texture;
    Texture* shadowMapTexture;

    void collisionCheck(GameObject* gameObject);

};

