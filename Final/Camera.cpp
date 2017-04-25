#include "Camera.h"


Camera::Camera()
{
	camPosition = Ray(0, 0, 0);
	camDirection = Ray(0, 0, 1);
	camRight = Ray(0, 0, 0);
	camDown = Ray(0, 0, 0);
}

Camera::Camera(Ray position, Ray direction, Ray right, Ray down)
{
	camPosition = position;
	camDirection = direction;
	camRight = right;
	camDown = down;
}

Camera::~Camera()
{
}

Ray Camera::getCameraPosition()
{
	return camPosition;
}

Ray Camera::getCameraDirection()
{
	return camDirection;
}

Ray Camera::getCameraRight()
{
	return camRight;
}

Ray Camera::getCameraDown()
{
	return camDown;
}
