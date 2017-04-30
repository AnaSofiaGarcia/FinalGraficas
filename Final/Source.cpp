#include "Source.h"

Source::Source()
{
}

Ray Source::getLightPosition()
{
	return Ray(0, 0, 0);
}

Color Source::getLightColor()
{
	return Color(1, 1, 1, 0);
}
