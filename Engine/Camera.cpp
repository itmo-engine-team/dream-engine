#include "Engine.h"
#include "Camera.h"
#include "GameMath.h"

Camera::Camera(Engine* engine, Vector3 position, Vector3 direction) : direction(direction)
{
	transform.SetWorldPosition(position);
	
	projectionMatrix = Matrix::CreatePerspectiveFieldOfView(
		120, 
		static_cast<float>(engine->GetScreenWidth()) / static_cast<float>(engine->GetScreenHeight()),
		0.01f, 100.0f);
}

Matrix Camera::getViewMatrix()
{
	Vector3 target = Vector3::Transform(direction, transform.GetWorldMatrix());
	Vector3 up = { 0, 1, 0 };
	return Matrix::CreateLookAt(transform.GetWorldPosition(), target, up);
}

Matrix Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

void Camera::rotate(float dx, float dy)
{
	transform.AddLocalRotation(Vector3::UnitY, dx * rotationSpeed);
	transform.AddLocalRotation(Vector3::UnitX, dy * rotationSpeed);
}

void Camera::translate(Vector3 translation)
{
	transform.AddLocalPosition(translation);
}

void Camera::update()
{
}
