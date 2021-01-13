#pragma once

#include "SimpleMath.h"
#include <vector>

using namespace DirectX::SimpleMath;

class Transform
{

public:

    Transform(Vector3 pos = Vector3::Zero);
    ~Transform();

    Transform* GetParent() const;
    bool HasParent() const;
    void SetParent(Transform* parent, bool saveRelation = false);
    void ClearParent();

    std::vector<Transform*>& GetChildren();
    void AddChild(Transform* child);
    void RemoveChild(Transform* childToRemove);

    void SetLocalTransform(Vector3 pos, Vector3 rotation, Vector3 scale);
    void SetLocalPosition(Vector3 pos);
    void AddLocalPosition(Vector3 pos);
    void SetLocalRotation(Vector3 rotation);
    void AddLocalRotation(Vector3 axis, float angle);
    void SetLocalScale(Vector3 scale);

    // Relates on parent
    Vector3 GetRelativePosition() const;
    void SetRelativePosition(Vector3 pos);
    void AddRelativePosition(Vector3 pos);
    void AddRelativeRotation(Vector3 axis, float angle);

    Vector3 GetWorldPosition() const;
    void SetWorldPosition(Vector3 pos);
    void AddWorldPosition(Vector3 pos);
    void AddWorldRotation(Vector3 axis, float angle);
    Vector3 GetWorldScale() const;

    Matrix GetWorldMatrix() const;

private:

    // Transform matrix from local to parent
    Matrix relativeMatrix = Matrix::Identity;

    Transform* parent = nullptr;
    std::vector<Transform*> children;

    void clearParentWithRecursive(bool recursiveClearing);
    void removeChildWithRecursive(Transform* childToRemove, bool recursiveClearing);

};

