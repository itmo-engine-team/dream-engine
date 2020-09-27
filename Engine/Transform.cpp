#include "Transform.h"

Transform::Transform(const Vector3 pos)
{
    transformMatrix = Matrix::CreateFromQuaternion(Quaternion::Identity)
        * Matrix::CreateTranslation(pos);
}

Transform::~Transform()
{
    parent->RemoveChild(this, false);

    for (auto pChild : children)
    {
        pChild->ClearParent(false);
    }
}

Transform* Transform::GetParent() const
{
    return parent;
}

bool Transform::HasParent() const
{
    return parent != nullptr;
}

void Transform::SetParent(Transform* parent)
{
    if (parent == nullptr)
    {
        // @TODO Wait for LOGGER
        // LOG WARNING
        return;
    }

    ClearParent(true);

    parent->children.push_back(this);
    this->parent = parent;
}

void Transform::ClearParent()
{
    ClearParent(true);
}

void Transform::ClearParent(const bool recursiveClearing)
{
    if (parent == nullptr)
    {
        return;
    }

    if (recursiveClearing)
    {
        // Find this in parent children list to remove
        const auto iterator = parent->children.begin();
        for (auto child : parent->children)
        {
            if (child == this)
            {
                parent->children.erase(iterator);
                break;
            }
        }
    }

    parent = nullptr;
}

void Transform::AddChild(Transform* child)
{
    if (child == nullptr)
    {
        // @TODO Wait for LOGGER
        // LOG WARNING
        return;
    }

    children.push_back(child);
    child->parent = this;
    child->transformMatrix *= GetWorldMatrix().Invert();
}

void Transform::RemoveChild(Transform* childToRemove)
{
    RemoveChild(childToRemove, true);
}

void Transform::RemoveChild(Transform* childToRemove, const bool recursiveClearing)
{
    if (childToRemove == nullptr)
    {
        return;
    }

    // Find child to remove
    const auto iterator = children.begin();
    for (auto pChild : children)
    {
        if (pChild == childToRemove)
        {
            children.erase(iterator);
            break;
        }
    }

    if (recursiveClearing)
    {
        childToRemove->ClearParent(false);
    }
}

std::vector<Transform*>& Transform::GetChildren()
{
    return children;
}

Vector3 Transform::GetLocalPosition() const
{
    return translation.Translation();
}

void Transform::SetLocalPosition(const Vector3 pos)
{
    transformMatrix = translation.Invert() * transformMatrix;
    translation = Matrix::CreateTranslation(pos);
    transformMatrix *= translation;
}

void Transform::AddLocalPosition(const Vector3 pos)
{
    transformMatrix = Matrix::CreateTranslation(pos) * transformMatrix;
    translation *= Matrix::CreateTranslation(pos);
}

Vector3 Transform::GetWorldPosition() const
{
    return GetWorldMatrix().Translation();
}

void Transform::SetWorldPosition(const Vector3 pos)
{
    transformMatrix = transformMatrix * translation.Invert();
    translation = Matrix::CreateTranslation(pos);
    transformMatrix *= translation;
}

void Transform::AddWorldPosition(const Vector3 pos)
{
    transformMatrix = transformMatrix * Matrix::CreateTranslation(pos);
    translation *= Matrix::CreateTranslation(pos);
}

void Transform::AddLocalRotation(const Vector3 axis, const float angle)
{
    rotation *= Matrix::CreateFromAxisAngle(axis, angle);
    transformMatrix = Matrix::CreateFromAxisAngle(axis, angle) * transformMatrix * translation.Invert() * translation;
}

void Transform::AddWorldRotation(const Vector3 axis, const float angle)
{
    rotation *= Matrix::CreateFromAxisAngle(axis, angle);
    transformMatrix = transformMatrix * translation.Invert() * Matrix::CreateFromAxisAngle(axis, angle) * translation;
}

Matrix Transform::GetWorldMatrix() const
{
    auto result = transformMatrix;

    if (parent != nullptr)
    {
        result *= parent->GetWorldMatrix();
    }

    return result;
}
