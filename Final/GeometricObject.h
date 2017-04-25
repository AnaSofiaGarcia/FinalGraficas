#pragma once
#include "Ray.h"
#include "Line.h"
#include "Color.h"

class GeometricObject
{
public:
	GeometricObject();
	~GeometricObject();

	Color getColor();
	Ray getNormal(Ray intersectionPosition);

	double findIntersection(Line line);
};

