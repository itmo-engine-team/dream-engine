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
    void SetParent(Transform* parent, bool saveRelation = false);
    void ÑlearParent();

    std::vector<Transform*>& GetChildren();
    void AddChild(Transform* child);
    void RemoveChild(Transform* childToRemove);

    void SetLocalPosition(Vector3 pos);
    void AddLocalPosition(Vector3 pos);
    void AddLocalRotation(Vector3 axis, float angle);

    // Relates on parent
    Vector3 GetRelativePosition() const;
    void SetRelativePosition(Vector3 pos);
    void AddRelativePosition(Vector3 pos);
    void AddRelativeRotation(Vector3 axis, float angle);

    Vector3 GetWorldPosition() const;
    void SetWorldPosition(Vector3 pos);
    void AddWorldPosition(Vector3 pos);
    void AddWorldRotation(Vector3 axis, float angle);

    Matrix GetWorldMatrix() const;

private:

    // Transform matrix from local to parent
    Matrix relativeMatrix = Matrix::Identity;

    Transform* parent = nullptr;
    std::vector<Transform*> children;

    void ÑlearParent(bool recursiveClearing);
    void RemoveChild(Transform* childToRemove, bool recursiveClearing);

};

