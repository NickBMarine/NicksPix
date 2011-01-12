#pragma once
#include "Color.h"
//=== class Span =============================
//This class records the corresponding x edges
//of equivalent y values of the triangle.
//============================================
struct Span
{
	Color _color1, _color2;
	float _x1, _x2;
	float _w1, _w2;
	float _z1, _z2;
	float _u1, _u2;
	float _v1, _v2;

	Span(const Color& color1, int x1, float z1, float u1, float v1, float w1, 
		 const Color& color2, int x2, float z2, float u2, float v2, float w2);
	~Span(void){};
}; // end of class Span