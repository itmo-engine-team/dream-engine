#pragma once

#include "Engine/RenderedGameObject.h"

class PyramidObject : public RenderedGameObject
{

public:
	PyramidObject(Game* game, Shader* shader, Vector3 position, Vector4 color);

	void preDraw();
private:
	float m_rotateDelta;
};

