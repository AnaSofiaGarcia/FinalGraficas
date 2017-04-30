#pragma once
#include "Ray.h"
#include "Color.h"

class Source {
public:
	Source();

	virtual Ray getLightPosition();
	virtual Color getLightColor();
};


