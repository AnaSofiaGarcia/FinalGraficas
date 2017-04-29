#pragma once

#include "Ray.h"
#include "Line.h"
#include "Color.h"

class GeometricObject {

public:
	GeometricObject();

	virtual Color getColor();
	virtual Ray getNormalAt(Ray intersectionPosition);

	virtual double findIntersection(Line line);
};
