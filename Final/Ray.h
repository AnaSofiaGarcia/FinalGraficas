#pragma once

#include "math.h"

class Ray {
	double x;
	double y;
	double z;

public:
	Ray();
	Ray(double, double, double);

	double getRayX();
	double getRayY();
	double getRayZ();
	double magnitude();
	Ray normalize();
	Ray negative();
	double dotProduct(Ray  v);
	Ray crossProduct(Ray v);
	Ray addRay(Ray v);
	Ray multRay(double scalar);
};