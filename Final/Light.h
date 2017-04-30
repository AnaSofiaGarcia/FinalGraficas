#include "Source.h"
#include "Ray.h"
#include "Color.h"

class Light : public Source {
	Ray _position;
	Color _color;

public:
	Light();
	Light(Ray, Color);

	virtual Ray getLightPosition();
	virtual Color getLightColor();
};

