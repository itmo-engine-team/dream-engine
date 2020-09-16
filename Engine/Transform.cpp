#include "Transform.h"

Transform::Transform(Vector3 pos)
{
	m_transformMatrix = Matrix::CreateFromQuaternion(Quaternion::Identity) * Matrix::CreateTranslation(pos);
}

Transform& Transform::getParent() const
{
	return *parent;
}

std::vector<std::shared_ptr<Transform>>& Transform::getChild()
{
	return children;
}

void Transform::addChild(Transform* obj)
{
	children.push_back(std::unique_ptr<Transform>(obj));
	obj->parent = std::unique_ptr<Transform>(this);
	obj->m_transformMatrix *= getWorldMatrix().Invert();
}

void Transform::setParent(Transform* p)
{
	parent = std::unique_ptr<Transform>(p);
	p->children.push_back(std::unique_ptr<Transform>(this));
	m_transformMatrix *= p->getWorldMatrix().Invert();
}

Vector3 Transform::getLocalPosition() const
{
	return m_Translation.Translation();
}

void Transform::setLocalPosition(Vector3 pos)
{
	m_transformMatrix = m_Translation.Invert() * m_transformMatrix;
	m_Translation = Matrix::CreateTranslation(pos);
	m_transformMatrix *= m_Translation;
}

void Transform::addLocalPosition(Vector3 pos)
{
	m_transformMatrix = Matrix::CreateTranslation(pos) * m_transformMatrix;
	m_Translation *= Matrix::CreateTranslation(pos);
}

Vector3 Transform::getWorldPosition() const
{
	return getWorldMatrix().Translation();
}

void Transform::setWorldPosition(Vector3 pos)
{
	m_transformMatrix = m_transformMatrix * m_Translation.Invert();
	m_Translation = Matrix::CreateTranslation(pos);
	m_transformMatrix *= m_Translation;
}

void Transform::addWorldPosition(Vector3 pos)
{
	m_transformMatrix = m_transformMatrix * Matrix::CreateTranslation(pos);
	m_Translation *= Matrix::CreateTranslation(pos);
}

void Transform::addLocalRotation(Vector3 axis, float angle)
{
	m_Rotation *= Matrix::CreateFromAxisAngle(axis, angle);
	m_transformMatrix = Matrix::CreateFromAxisAngle(axis, angle) * m_transformMatrix * m_Translation.Invert() * m_Translation;
}

void Transform::addWorldRotation(Vector3 axis, const float angle)
{
	m_Rotation *= Matrix::CreateFromAxisAngle(axis, angle);
	m_transformMatrix = m_transformMatrix * m_Translation.Invert() * Matrix::CreateFromAxisAngle(axis, angle) * m_Translation;
}

Matrix Transform::getWorldMatrix() const
{
	auto result = m_transformMatrix;

	if (parent)
	{
		result *= parent->getWorldMatrix();
	}
	
	return result;
}
