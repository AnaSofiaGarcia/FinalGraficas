#include "Ray.h"

Ray::Ray()
{
	x = 0;
	y = 0;
	z = 0;
}

Ray::Ray(double i, double j, double k)
{
	x = i;
	y = j;
	z = k;
}

Ray::~Ray()
{
}

double Ray::getRayX()
{
	return x;
}

double Ray::getRayY()
{
	return y;
}

double Ray::getRayZ()
{
	return z;
}

double Ray::magnitude()
{
	return sqrt((x * x) + (y * y) + (z * z));
}

double Ray::dotProduct(Ray v)
{
	return x * v.getRayX() + y * v.getRayY() + z * v.getRayZ();
}

Ray Ray::normalize()
{
	double magnitude = sqrt((x * x) + (y * y) + (z * z));
	return Ray(x /magnitude, y /magnitude, z /magnitude);
}

Ray Ray::negative()
{
	return Ray(-x, -y, -z);
}

Ray Ray::crossProduct(Ray v)
{
	return Ray(y * v.getRayZ() - z * v.getRayY(),
		z * v.getRayX() - x * v.getRayZ(),
		x * v.getRayY() - y * v.getRayX());
}

Ray Ray::addRay(Ray v)
{
	return Ray(x + v.getRayX(), y + v.getRayY(), z + v.getRayZ());
}

Ray Ray::multRay(double scalar)
{
	return Ray(x * scalar, y * scalar, z * scalar);
}