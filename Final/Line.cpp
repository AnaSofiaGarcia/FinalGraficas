#include "Line.h"

Line::Line()
{
	_origin = Ray(0, 0, 0);
	_direction = Ray(1, 0, 0);
}

Line::Line(Ray origin, Ray direction)
{
	_origin = origin;
	_direction = direction;
}

Line::~Line()
{
}

Ray Line::getLineOrigin()
{
	return _origin;
}

Ray Line::getLineDirection()
{
	return _direction;
}
