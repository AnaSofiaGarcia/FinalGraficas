#pragma once

#include "math.h"
#include "Ray.h"

class Line {
	Ray _origin;
	Ray _direction;
public:
	Line();
	Line(Ray, Ray);

	Ray getLineOrigin();
	Ray getLineDirection();
};

