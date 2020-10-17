#pragma once

#include "Engine.h"
#include "SpectatorActor.h"
#include "KatamariSphere.h"
#include "CameraComponent.h"
#include "StaticModelComponent.h"
#include "TexturedShader.h"

class KatamariGame : public Game
{
public:

    KatamariGame();
    ~KatamariGame();

    void Init(Engine* engine) override;
    void Update() override;

    CameraComponent* GetCamera() const override;

private:

    SpectatorActor* spectatorActor;

    KatamariSphere* katamariPlayer;
    StaticModelComponent* playerSphere;

    Actor* plane;
    Actor* box1;
    Actor* box2;
    Actor* box3;

    ModelData* planeModel;
    ModelData* boxModel;
    ModelData* playerModel;

    Shader* shader;
    TexturedShader* texturedShader;
    Texture* texture;

    void collisionCheck(GameObject* gameObject);

};

