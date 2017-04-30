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