#pragma once

#include "Engine/Actor.h"

class BoxObject : public Actor
{

public:
	BoxObject(Game* game, Shader* shader, Vector3 position, Vector4 color, Vector3 boxSize);
};

