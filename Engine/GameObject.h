#pragma once
#include <d3d11.h>
#include "SimpleMath.h"
#include "Vertex.h"
#include <wrl/client.h>
#include "Transform.h"

using namespace Microsoft::WRL;
using namespace DirectX::SimpleMath;

class Game;

class GameObject
{
public:
	
	GameObject(Game* game, Vector3 position = Vector3::Zero);
	virtual ~GameObject() = default;

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	Transform* transform;

protected:
	Game* m_game;

};

