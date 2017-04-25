#include "GeometricObject.h"

GeometricObject::GeometricObject()
{
}

GeometricObject::~GeometricObject()
{
}

Color GeometricObject::getColor()
{
	return Color(0.0, 0.0, 0.0, 0);
}

Ray GeometricObject::getNormal(Ray intersectionPosition)
{
	return Ray(0, 0, 0);
}

double GeometricObject::findIntersection(Line line)
{
	return 0;
}
