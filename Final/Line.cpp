#include "Line.h"

Line::Line()
{
	_origin = Ray(0, 0, 0);
	_direction = Ray(1, 0, 0);
}

Line::Line(Ray o, Ray d)
{
	_origin = o;
	_direction = d;
}

Ray Line::getLineOrigin()
{
	return _origin;
}

Ray Line::getLineDirection()
{
	return _direction;
}
