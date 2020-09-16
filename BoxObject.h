#pragma once

#include "Engine/RenderedGameObject.h"

class BoxObject : public RenderedGameObject
{

public:
	BoxObject(Game* game, Shader* shader, Vector3 position, Vector4 color, Vector3 boxSize);
};

