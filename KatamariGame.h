#pragma once
#include "Engine/Game.h"
#include "BoxObject.h"
#include "Engine/ModelObject.h"
#include "KatamariSphere.h"
#include "Engine/TexturedShader.h"
#include "Engine/Shader.h"
#include "SceneGameObject.h"

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
	SceneGameObject* katamariPlayer;
	KatamariSphere* katamariSphere;
	BoxObject* plane;
	BoxObject* box1;
	BoxObject* box2;
	BoxObject* box3;

	Shader* shader;
	TexturedShader* texturedShader;
	Texture* texture;
};

