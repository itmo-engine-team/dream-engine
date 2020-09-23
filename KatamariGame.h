#pragma once
#include "Engine/Game.h"
#include "KatamariSphere.h"
#include "Engine/TexturedShader.h"
#include "Engine/Shader.h"
#include "Engine/StaticModelComponent.h"

using namespace DirectX::SimpleMath;

class KatamariGame : public Game
{
public:

	KatamariGame(HINSTANCE hInstance, WNDCLASSEX wc);
	~KatamariGame();

	void init() override;

protected:

	void update() override;
	void drawObjects();
	void collisionCheck(GameObject* gameObject);

private:

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

};

