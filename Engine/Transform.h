#pragma once

#include <d3d11.h>
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

struct Transform
{
public:
	Transform() = default;
	Transform(Vector3 pos);
	~Transform() = default;

	Transform& getParent() const;
	std::vector<std::shared_ptr<Transform>>& getChild();
	void addChild(Transform* obj);
	void setParent(Transform* parent);

	Vector3 getLocalPosition() const;
	void setLocalPosition(Vector3 pos);
	void addLocalPosition(Vector3 pos);
	
	Vector3 getWorldPosition() const;
	void setWorldPosition(Vector3 pos);
	void addWorldPosition(Vector3 pos);

	std::unique_ptr<Transform> parent = nullptr;
	std::vector<std::shared_ptr<Transform>> children;

	void addLocalRotation(Vector3 axis, float angle);
	void addWorldRotation(Vector3 axis, float angle);

	Matrix getWorldMatrix() const;
	Matrix m_transformMatrix = Matrix::Identity;
	Matrix m_Translation = Matrix::Identity;
	Matrix m_Rotation = Matrix::Identity;
	Matrix m_Scale = Matrix::Identity;
};

