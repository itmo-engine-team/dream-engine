#include "Transform.h"

Transform::Transform(const Vector3 pos)
{
    relativeMatrix = Matrix::CreateTranslation(pos);
}

Transform::~Transform()
{
    parent->removeChildWithRecursive(this, false);

    for (auto pChild : children)
    {
        pChild->clearParentWithRecursive(false);
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

void Transform::SetParent(Transform* parent, const bool saveRelation)
{
    if (parent == nullptr)
    {
        return;
    }

    clearParentWithRecursive(true);

    parent->children.push_back(this);
    this->parent = parent;

    if (saveRelation)
    {
        relativeMatrix *= parent->GetWorldMatrix();
    }

    relativeMatrix *= parent->GetWorldMatrix().Invert();
}

void Transform::ClearParent()
{
    clearParentWithRecursive(true);
}

void Transform::clearParentWithRecursive(const bool recursiveClearing)
{
    if (parent == nullptr)
    {
        return;
    }

    relativeMatrix *= parent->GetWorldMatrix();

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
        return;
    }

    children.push_back(child);
    child->parent = this;
    child->relativeMatrix *= GetWorldMatrix().Invert();
}

void Transform::RemoveChild(Transform* childToRemove)
{
    removeChildWithRecursive(childToRemove, true);
}

void Transform::removeChildWithRecursive(Transform* childToRemove, const bool recursiveClearing)
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
        childToRemove->clearParentWithRecursive(false);
    }
}

std::vector<Transform*>& Transform::GetChildren()
{
    return children;
}

Vector3 Transform::GetRelativePosition() const
{
    return relativeMatrix.Translation();
}

void Transform::SetLocalPosition(const Vector3 pos)
{
    const auto prevTranslation = Matrix::CreateTranslation(relativeMatrix.Translation());
    relativeMatrix = prevTranslation.Invert() * relativeMatrix;
    relativeMatrix = Matrix::CreateTranslation(pos) * relativeMatrix;
}

void Transform::AddLocalPosition(const Vector3 pos)
{
    relativeMatrix = Matrix::CreateTranslation(pos) * relativeMatrix;
}

void Transform::SetRelativePosition(Vector3 pos)
{
    relativeMatrix *= Matrix::CreateTranslation(relativeMatrix.Translation()).Invert();
    relativeMatrix *= Matrix::CreateTranslation(pos);
}

void Transform::AddRelativePosition(Vector3 pos)
{
    relativeMatrix *= Matrix::CreateTranslation(pos);
}

Vector3 Transform::GetWorldPosition() const
{
    return GetWorldMatrix().Translation();
}

void Transform::SetWorldPosition(const Vector3 pos)
{
    const auto prevTranslation = Matrix::CreateTranslation(GetWorldMatrix().Translation());
    relativeMatrix = GetWorldMatrix() * prevTranslation.Invert();
    relativeMatrix *= Matrix::CreateTranslation(pos);

    if (parent)
    {
        relativeMatrix *= parent->GetWorldMatrix().Invert();
    }
}

void Transform::AddWorldPosition(const Vector3 pos)
{
    relativeMatrix = GetWorldMatrix() * Matrix::CreateTranslation(pos);

    if (parent)
    {
        relativeMatrix *= parent->GetWorldMatrix().Invert();
    }
}

void Transform::AddLocalRotation(const Vector3 axis, const float angle)
{
    relativeMatrix = Matrix::CreateFromAxisAngle(axis, angle) * relativeMatrix;
}

void Transform::AddRelativeRotation(Vector3 axis, float angle)
{
    relativeMatrix *= Matrix::CreateFromAxisAngle(axis, angle);
}

void Transform::AddWorldRotation(const Vector3 axis, const float angle)
{
    relativeMatrix = GetWorldMatrix() * Matrix::CreateFromAxisAngle(axis, angle);

    if (parent)
    {
        relativeMatrix *= parent->GetWorldMatrix().Invert();
    }
}

Matrix Transform::GetWorldMatrix() const
{
    auto result = relativeMatrix;

    if (parent != nullptr)
    {
        result *= parent->GetWorldMatrix();
    }

    return result;
}
