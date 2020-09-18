#pragma once

#include "Engine/Actor.h"

class PyramidObject : public Actor
{

public:
	PyramidObject(Game* game, Shader* shader, Vector3 position, Vector4 color);

	void preDraw();
private:
	float m_rotateDelta;
};

