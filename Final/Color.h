#pragma once

class Color {
	double _red;
	double _green; 
	double _blue; 
	double _special;

public:
	Color();
	Color(double, double, double, double);

	double getColorRed();
	double getColorGreen();
	double getColorBlue();
	double getColorSpecial();

	double setColorRed(double redValue);
	double setColorGreen(double greenValue);
	double setColorBlue(double blueValue);
	double setColorSpecial(double specialValue);

	double brightness();
	Color colorScalar(double scalar);
	Color colorAdd(Color color);
	Color colorMultiply(Color color);
	Color colorAverage(Color color);
	Color clip();
};