#include "Light.h"

Light::Light()
{
	_position = Ray(0, 0, 0);
	_color = Color(1, 1, 1, 0);
}

Light::Light(Ray p, Color c) {
	_position = p;
	_color = c;
}

Ray Light::getLightPosition()
{
	return _position;
}

Color Light::getLightColor()
{
	return _color;
}
