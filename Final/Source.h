#pragma once
#include "Ray.h"
#include "Color.h"

class Source
{
public:
	Source();
	~Source();

	Ray getLightPosition();
	Color getLightColor();
};

