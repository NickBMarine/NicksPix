#include "Span.h"

Span::Span(const Color& color1, int x1, float z1, float u1, float v1, float w1,
		   const Color& color2, int x2, float z2, float u2, float v2, float w2)
{
	if ( x1 < x2)
	{
		m_color1 = color1;
		X1 = x1;
		Z1 = z1;
		U1 = u1;
		V1 = v1;
		W1 = w1;
		m_color2 = color2;
		X2 = x2;
		Z2 = z2;
		U2 = u2;
		V2 = v2;
		W2 = w2;
	}
	else
	{
		m_color1 = color2;
		X2 = x1;
		Z2 = z1;
		U2 = u1;
		V2 = v1;
		W2 = w1;
		m_color2 = color1;
		X1 = x2;
		Z1 = z2;
		U1 = u2;
		V1 = v2;
		W1 = w2;
	}
}

