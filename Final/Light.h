#pragma once
#include "Ray.h"
#include "Color.h"
#include "Source.h"

class Light : public Source
{
public:
	Light();
	Light(Ray p, Color c);
	~Light();

	Ray getLightPosition();
	Color getLightColor();

private:
	Ray _position;
	Color _color;
};

