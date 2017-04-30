#include "Camera.h"

Camera::Camera()
{
	_camPos = Ray(0, 0, 0);
	_camDir = Ray(0, 0, 1);
	_camRight = Ray(0, 0, 0);
	_camDown = Ray(0, 0, 0);
}

Camera::Camera(Ray position, Ray direction, Ray right, Ray down)
{
	_camPos = position;
	_camDir = direction;
	_camRight = right;
	_camDown = down;
}

Ray Camera::getCameraPosition()
{
	return _camPos;
}

Ray Camera::getCameraDirection()
{
	return _camDir;
}

Ray Camera::getCameraRight()
{
	return _camRight;
}

Ray Camera::getCameraDown()
{
	return _camDown;
}


glm::mat4 Camera::GetViewProjection()
{
	return _projectionMatrix * _viewMatrix;
}

glm::mat4 Camera::GetViewMatrix()
{
	return _viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return _projectionMatrix;
}

void Camera::SetPosition(float x, float y, float z)
{
	_transform.SetPosition(x, y, z);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::SetPosition(glm::vec3 position)
{
	_transform.SetPosition(position);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::SetRotation(float x, float y, float z)
{
	_transform.SetRotation(x, y, z);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::SetRotation(glm::vec3 rotation)
{
	_transform.SetRotation(rotation);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::MoveForward(float delta, bool world)
{
	_transform.MoveForward(delta, world);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::MoveUp(float delta, bool world)
{
	_transform.MoveUp(delta, world);
	_viewMatrix = glm::inverse(_transform.GetModelMatrix());
}

void Camera::MoveRight(float delta, bool world)
{
	_transform.MoveRight(delta, world);
	_viewMatrix =glm::inverse(_transform.GetModelMatrix());
}

void Camera::SetOrthographic(float size, float aspectRatio)
{
	float xSize = aspectRatio * size;
	_projectionMatrix = glm::ortho(-xSize, xSize, -size, size, -size, size);
}

glm::vec3 Camera::getPosition()
{
	return _transform.GetPosition();
}