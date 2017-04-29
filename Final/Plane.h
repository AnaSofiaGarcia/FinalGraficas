#pragma once

#include "Ray.h"
#include "GeometricObject.h"
#include "math.h"
#include "Color.h"

class Plane : public GeometricObject {
	Ray _normal;
	double _distance;
	Color _color;

public:
	Plane();
	Plane(Ray, double, Color);


	Ray getPlaneNormal();
	double getPlaneDistance();
	virtual Color getColor();

	virtual Ray getNormalAt(Ray point);
	virtual double findIntersection(Line line);
};