#pragma once

class Color
{
public:
	Color();
	Color(double r, double g, double b, double a);
	~Color();

	double getColorRed();
	double getColorGreen();
	double getColorBlue();
	double getColorAlpha();

	double setColorRed(double redValue);
	double setColorGreen(double greenValue);
	double setColorBlue(double blueValue);
	double setColorAlpha(double alphaValue);

	double brightness();

	Color colorScalar(double scalar);
	Color colorAdd(Color color);
	Color colorMultiply(Color color);
	Color colorAverage(Color color);
	Color clip();

private:
	double _red;
	double _green;
	double _blue;
	double _alpha;
};
