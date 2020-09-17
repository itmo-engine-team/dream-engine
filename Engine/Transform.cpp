#include "Transform.h"

Transform::Transform(const Vector3 pos)
{
	transformMatrix = Matrix::CreateFromQuaternion(Quaternion::Identity)
        * Matrix::CreateTranslation(pos);
}

Transform::~Transform()
{
	pParent->RemoveChild(this, false);

    for (auto pChild : children)
    {
		pChild->ClearParent(false);
    }
}

Transform* Transform::GetParent() const
{
	return pParent;
}

bool Transform::HasParent() const
{
	return pParent != nullptr;
}

void Transform::SetParent(Transform* pParent)
{
	if (pParent == nullptr)
	{
	    // @TODO Wait for LOGGER
	    // LOG WARNING
	    return;
	}

	ClearParent();

	pParent->children.push_back(this);
	this->pParent = pParent;
	transformMatrix *= pParent->GetWorldMatrix().Invert();
}

void Transform::ClearParent(const bool recursiveClearing)
{
	if (pParent == nullptr)
	{
		return;
	}

	if (recursiveClearing)
	{
		// Find this in parent children list to remove
		const auto iterator = pParent->children.begin();
		for (auto child : pParent->children)
		{
			if (child == this)
			{
				pParent->children.erase(iterator);
				break;
			}
		}
	}

	transformMatrix *= pParent->GetWorldMatrix();
	pParent = nullptr;
}

void Transform::AddChild(Transform* pChild)
{
	if (pChild == nullptr)
	{
		// @TODO Wait for LOGGER
		// LOG WARNING
		return;
	}

	children.push_back(pChild);
	pChild->pParent = this;
	pChild->transformMatrix *= GetWorldMatrix().Invert();
}

void Transform::RemoveChild(Transform* pChildToRemove, const bool recursiveClearing)
{
	if (pChildToRemove == nullptr)
	{
		return;
	}

	// Find child to remove
	const auto iterator = children.begin();
	for (auto pChild : children)
	{
		if (pChild == pChildToRemove)
		{
			children.erase(iterator);
			break;
		}
	}

	if (recursiveClearing)
	{
		pChildToRemove->ClearParent(false);
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

	if (pParent != nullptr)
	{
		result *= pParent->GetWorldMatrix();
	}
	
	return result;
}
