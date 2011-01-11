#pragma once
#include "Color.h"
//=== class Span =============================
//This class records the corresponding x edges
//of equivalent y values of the triangle.
//============================================
class Span
{
public:
	Color m_color1, m_color2;
	float X1, X2;
	float W1, W2;
	float Z1, Z2;
	float U1, U2;
	float V1, V2;

	Span(const Color& color1, int x1, float z1, float u1, float v1, float w1, 
		 const Color& color2, int x2, float z2, float u2, float v2, float w2);
	~Span(void){};
}; // end of class Span