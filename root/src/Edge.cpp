#include "Edge.h"

Edge::Edge(const Color &color1, int x1, int y1, float z1, float u1, float v1, float w1,
		   const Color &color2, int x2, int y2, float z2, float u2, float v2, float w2)
{
	if ( y1 < y2)
	{
		_color1 = color1;
		_y1 = y1;
		_x1 = x1;
		_z1 = z1;
		_u1 = u1;
		_v1 = v1;
		_w1 = w1;
		_color2 = color2;
		_y2 = y2;
		_x2 = x2;
		_z2 = z2;
		_u2 = u2;
		_v2 = v2;
		_w2 = w2;
	}
	else
	{
		_color1 = color2;
		_y1 = y2;
		_x1 = x2;
		_z1 = z2;
		_u1 = u2;
		_v1 = v2;
		_w1 = w2;
		_color2 = color1;
		_y2 = y1;
		_x2 = x1;
		_z2 = z1;
		_u2 = u1;
		_v2 = v1;
		_w2 = w1;

	}
}
