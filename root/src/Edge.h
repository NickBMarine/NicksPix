#pragma once
#include "Color.h"
#include "PixelToaster.h"
#include <math.h>
using namespace PixelToaster;

//=== class Edge ==============================
//The purpose of this class is to map the edges
//of the triangle.
//=============================================
class Edge
{
public:
	Color _color1, _color2;
	int _x1, _y1, _x2, _y2;
	float _w1, _w2;
	float _z1, _z2;
	float _u1, _u2;
	float _v1, _v2;
	Edge(const Color &color1, int x1, int y1, float z1, float u1, float v1, float w1,
		 const Color &color2, int x2, int y2, float z2, float u2, float v2, float w2);
	Edge(){};
	~Edge(void){};
};// end of class Edge