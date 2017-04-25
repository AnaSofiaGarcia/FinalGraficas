#pragma once
#include "math.h"
#include "Ray.h"

class Line
{
public:
	Line();
	Line(Ray, Ray);
	~Line();

	Ray getLineOrigin();
	Ray getLineDirection();

private: 
	Ray _origin;
	Ray _direction
};

