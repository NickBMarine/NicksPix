#pragma once
#include <windows.h>

struct Color
{
	float r, g, b;
	Color() : r(0), g(0), b(0) {};
	Color(int red, int green, int blue);
	Color(float red, float green, float blue);
	Color operator+(const Color &c) const;
	Color operator-(const Color &c) const;
	Color operator*(float f) const;
	Color operator/(float f) const;
	bool operator!=(float f) const;
	bool operator==(float f) const;

	~Color(void){};
};

