#pragma once
#include "Ray.h"
#include "Color.h"
#include "GeometricObject.h"
#include "math.h"
//#include <glm/glm.hpp>


class Sphere : public GeometricObject
{
public:
	Sphere();
	Sphere(Ray centerValue, double radiusValue, Color colorValue);
	~Sphere();

	Ray getSphereCenter();
	double getSphereRadius();
	Color getColor();
	Ray getNormal(Ray point);
	double findIntersection(Line line);
	 

private: 
	Ray _center;
	double _radius;
	Color _color;
};
