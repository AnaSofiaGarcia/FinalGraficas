#pragma once

#include "Ray.h"
#include "GeometricObject.h"
#include "math.h"
#include "Color.h"

class Sphere : public GeometricObject {
	Ray _center;
	double _radius;
	Color _color;
public:
	Sphere();
	Sphere(Ray, double, Color);

	Ray getSphereCenter();
	double getSphereRadius();
	virtual Color getColor();
	virtual Ray getNormalAt(Ray point);
	virtual double findIntersection(Line line);
};
