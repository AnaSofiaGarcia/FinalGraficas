#include "Sphere.h"

Sphere::Sphere()
{
	_center = Ray(0, 0, 0);
	_radius = 1.0;
	_color = Color(0.5, 0.5, 0.5, 0);
}

Sphere::Sphere(Ray centerValue, double radiusValue, Color colorValue) {
	_center = centerValue;
	_radius = radiusValue;
	_color = colorValue;
}

Ray Sphere::getSphereCenter()
{
	return _center;
}

double Sphere::getSphereRadius()
{
	return _radius;
}

Color Sphere::getColor()
{
	return _color;
}

Ray Sphere::getNormalAt(Ray point)
{
	Ray normalRay = point.addRay(_center.negative()).normalize();
	return normalRay;
}

double Sphere::findIntersection(Line line)
{
	Ray lineOrigin = line.getLineOrigin();
	double lineOriginX = lineOrigin.getRayX();
	double lineOriginY = lineOrigin.getRayY();
	double lineOriginZ = lineOrigin.getRayZ();

	Ray lineDirection = line.getLineDirection();
	double lineDirectionX = lineDirection.getRayX();
	double lineDirectionY = lineDirection.getRayY();
	double lineDirectionZ = lineDirection.getRayZ();

	Ray sphereCenter = _center;
	double sphereCenterX = sphereCenter.getRayX();
	double sphereCenterY = sphereCenter.getRayY();
	double sphereCenterZ = sphereCenter.getRayZ();

	double a = 1;
	double b = (2 * (lineOriginX - sphereCenterX) * lineDirectionX) + (2 * (lineOriginY - sphereCenterY) * lineDirectionY) + (2 * (lineOriginZ - sphereCenterZ) * lineDirectionZ);
	double c = pow(lineOriginX - sphereCenterX, 2) + pow(lineOriginY - sphereCenterY, 2) + pow(lineOriginZ - sphereCenterZ, 2) - (_radius * _radius);
	double discriminant = b * b - 4 * c;
	if (discriminant > 0) {
		double root_1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.000001;

		if (root_1 > 0) {
			return root_1;
		}
		else {
			double root_2 = ((sqrt(discriminant) - b) / 2) - 0.000001;
			return root_2;
		}
	}
	else {
		return -1;
	}
}
