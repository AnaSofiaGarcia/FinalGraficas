#include "Color.h"

Color::Color()
{
	_red = 0.5;
	_green = 0.5;
	_blue = 0.5;
}

Color::Color(double r, double g, double b, double a)
{
	_red = r;
	_green = g;
	_blue = b;
	_alpha = a;
}

Color::~Color()
{
}

double Color::getColorRed()
{
	return _red;
}

double Color::getColorGreen()
{
	return _green;
}

double Color::getColorBlue()
{
	return _blue;
}

double Color::getColorAlpha()
{
	return _alpha;
}

double Color::setColorRed(double redValue)
{
	return redValue;
}

double Color::setColorGreen(double greenValue)
{
	return greenValue;
}

double Color::setColorBlue(double blueValue)
{
	return blueValue;
}

double Color::setColorAlpha(double alphaValue)
{
	return alphaValue;
}

double Color::brightness()
{
	return (_red + _green + _blue) / 3;
}

Color Color::colorScalar(double scalar)
{
	return Color(_red * scalar, _green * scalar, _blue * scalar, _alpha);
}

Color Color::colorAdd(Color color)
{
	return Color(_red + color.getColorRed(), _green + color.getColorGreen(), _blue + color.getColorBlue, _alpha);
}

Color Color::colorMultiply(Color color)
{
	return Color(_red * color.getColorRed(), _green * color.getColorGreen(), _blue * color.getColorBlue, _alpha);
}

Color Color::colorAverage(Color color)
{
	return Color((_red + color.getColorRed()) / 2, (_green + color.getColorGreen()) / 2, (_blue + color.getColorBlue) / 2, _alpha);
}

Color Color::clip()
{
	double allLight = _red + _green + _blue;
	double excessLight = allLight - 3;
	if (excessLight > 0) {
		_red = _red + excessLight * (_red / allLight);
		_green = _green + excessLight * (_green / allLight);
		_blue = _blue + excessLight * (_blue / allLight);
	}

	if (_red > 1){ 
		_red = 1;
	}
	if (_green > 1){
		_green = 1;
	}
	if (_blue > 1){
		_blue = 1;
	}
	if (_red < 0){
		_red = 0;
	}
	if (_green < 0){
		_green = 0;
	}
	if (_blue < 0){
		_blue = 0;
	}

	return Color(_red, _green, _blue, _alpha);
}
