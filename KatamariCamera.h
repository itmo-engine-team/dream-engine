#pragma once
#include "Engine/Camera.h"
#include "Engine/GameObject.h"

class KatamariCamera : public Camera
{
public:

	KatamariCamera(Game* game, Vector3 position, GameObject* observedObject);
	void update() override;

private:
	Vector3 m_offset;
	GameObject* m_observedObject;
};

