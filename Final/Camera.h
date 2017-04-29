#pragma once
#pragma once

#include "Ray.h"

class Camera {
private:
	Ray _camPos;
	Ray _camDir;
	Ray _camRight;
	Ray _camDown;

public:
	Camera();
	Camera(Ray, Ray, Ray, Ray);

	Ray getCameraPosition();
	Ray getCameraDirection();
	Ray getCameraRight();
	Ray getCameraDown();

};

