#include "Color.h"

Color::Color(int red, int green, int blue)
{
	if ( red > 255)
		red = 255;
	if ( blue > 255)
		blue = 255;
	if ( green > 255)
		green = 255;

	r = (float)red / 255;
	g = (float)green / 255;
	b = (float)blue / 255;
}

Color::Color(float red, float green, float blue)
{
	if ( red > 1.0f )
		red = 1.0f;
	if ( green > 1.0f )
		green = 1.0f;
	if ( blue > 1.0f )
		blue = 1.0f;

	r = red;
	g = green;
	b = blue;

}

Color Color::operator+(const Color &c) const
{
	Color tempColor;
	
	tempColor.b = b + c.b;
	
	tempColor.r = r + c.r;
	
	tempColor.g = g + c.g;

	return tempColor;

}

Color Color::operator-(const Color &c) const
{
	Color tempColor;
	
	tempColor.b = b - c.b;
	
	tempColor.r = r - c.r;
	
	tempColor.g = g - c.g;

	return tempColor;
}

Color Color::operator*(float f) const
{
	Color tempColor;
	
	tempColor.b = b * f;
	
	tempColor.r = r * f;
	
	tempColor.g = g * f;

	return tempColor;
}

Color Color::operator/(float f) const
{
	Color tempColor;
	
	tempColor.b = b / f;
	
	tempColor.r = r / f;
	
	tempColor.g = g / f;

	return tempColor;
}

bool Color::operator!=(float f) const
{
	if ( r != f && g != f && b != f)
	{
		return true;
	}
	return false;
}

bool Color::operator==(float f) const 
{
	if ( r == f && g == f && b == f)
	{
		return true;
	}
	return false;
}