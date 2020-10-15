#pragma once

#include "../Engine.h"
#include "../InGame/GameObject/SpectatorActor.h"
#include "KatamariSphere.h"
#include "../InGame/GameObject/Component/CameraComponent.h"
#include "../InGame/GameObject/Component/StaticModelComponent.h"
#include "../Graphics/Shader/TexturedShader.h"

using namespace DirectX::SimpleMath;

class KatamariGame : public Game
{
public:

    KatamariGame(Engine* engine);
    ~KatamariGame();

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

