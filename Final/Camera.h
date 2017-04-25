#pragma once
#include "Ray.h"

class Camera
{
public:
	Camera();
	Camera(Ray position, Ray direction, Ray right, Ray down);
	~Camera();

	Ray getCameraPosition();
	Ray getCameraDirection();
	Ray getCameraRight();
	Ray getCameraDown();

private:
	Ray camPosition;
	Ray camDirection;
	Ray camRight;
	Ray camDown;
};

