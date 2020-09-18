#pragma once

#include "SimpleMath.h"
#include <wrl/client.h>

using namespace Microsoft::WRL;
using namespace DirectX::SimpleMath;

class Game;

class GameObject
{
public:
	
	GameObject(Game* game);
	virtual ~GameObject() = default;

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

protected:
	Game* pGame;
};

