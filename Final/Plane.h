#pragma once
#include "Ray.h"
#include "Color.h"
#include "GeometricObject.h"
#include "math.h"

class Plane : public GeometricObject
{
public:
	Plane();
	Plane(Ray normalValue, double distanceValue, Color colorValue);
	~Plane();

	Ray getPlaneNormal();
	double getPlaneDistance();
	Color getColor();
	Ray getNormal(Ray point);

	double findIntersection(Line line);

private:
	Ray _normal;
	double _distance;
	Color _color;
};
