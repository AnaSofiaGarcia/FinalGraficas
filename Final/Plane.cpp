#include "Plane.h"

Plane::Plane()
{
	_normal = Ray(1, 0, 0);
	_distance = 0;
	_color = Color(0.5, 0.5, 0.5, 0);
}

Plane::Plane(Ray normalValue, double distanceValue, Color colorValue)
{
	_normal = normalValue;
	_distance = distanceValue;
	_color = colorValue;
}

Plane::~Plane()
{
}

Ray Plane::getPlaneNormal()
{
	return _normal;
}

double Plane::getPlaneDistance()
{
	return _distance;
}

Color Plane::getColor()
{
	return _color;
}

Ray Plane::getNormal(Ray point)
{
	return _normal;
}

double Plane::findIntersection(Line line)
{
	Ray lineDirection = line.getLineDirection();
	double a = lineDirection.dotProduct(_normal);
	if (a == 0) {
		return -1;
	}
	else {
		double b = _normal.dotProduct(line.getLineOrigin().addRay(_normal.multRay(_distance).negative()));
		return -1 * b / a;
	}
}
