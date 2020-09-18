#pragma once

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class Transform
{

public:

	Transform(Vector3 pos = Vector3::Zero);

	~Transform();

	Transform* GetParent() const;
	bool HasParent() const;
	void SetParent(Transform* pParent);
	void ClearParent(bool recursiveClearing = true);

	std::vector<Transform*>& GetChildren();
	void AddChild(Transform* pChild);
	void RemoveChild(Transform* pChildToRemove, bool recursiveClearing = true);

	Vector3 GetLocalPosition() const;
	void SetLocalPosition(Vector3 pos);
	void AddLocalPosition(Vector3 pos);
	
	Vector3 GetWorldPosition() const;
	void SetWorldPosition(Vector3 pos);
	void AddWorldPosition(Vector3 pos);

	void AddLocalRotation(Vector3 axis, float angle);
	void AddWorldRotation(Vector3 axis, float angle);

	Matrix GetWorldMatrix() const;

private:

	Matrix transformMatrix = Matrix::Identity;
	Matrix translation = Matrix::Identity;
	Matrix rotation = Matrix::Identity;
	Matrix scale = Matrix::Identity;

	Transform* pParent = nullptr;
	std::vector<Transform*> children;

};

