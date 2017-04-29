#include "Plane.h"

Plane::Plane()
{
	_normal = Ray(1, 0, 0);
	_distance = 0;
	_color = Color(0.5, 0.5, 0.5, 0);
}

Plane::Plane(Ray normalValue, double distanceValue, Color colorValue) {
	_normal = normalValue;
	_distance = distanceValue;
	_color = colorValue;
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

Ray Plane::getNormalAt(Ray point)
{
	return _normal;
}

double Plane::findIntersection(Line linea)
{
	Ray lineDirection = linea.getLineDirection();
	double a = lineDirection.dotProduct(_normal);
	if (a == 0) {
		return -1;
	}
	else {
		double b = _normal.dotProduct(linea.getLineOrigin().addRay(_normal.multRay(_distance).negative()));
		return -1 * b / a;
	}
}

