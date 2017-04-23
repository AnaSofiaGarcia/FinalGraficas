#include "Ray.h"



Ray::Ray()
{
}

void Ray::CreatRay(glm::vec3 o, glm::vec3 d)
{
	o = _origin;
	d = _direction;
}


Ray::~Ray()
{
}
