#pragma once
//#include <glm/glm.hpp>
#include "math.h"

class Ray
{
public:
	Ray();
	Ray(double i, double j, double k);
	~Ray();

	double getRayX();
	double getRayY();
	double getRayZ();

	double magnitude();
	double dotProduct(Ray v);

	Ray normalize();
	Ray negative();
	Ray crossProduct(Ray v);
	Ray addRay(Ray v);
	Ray multRay(double scalar);

private:
	double x;
	double y;
	double z;
};
