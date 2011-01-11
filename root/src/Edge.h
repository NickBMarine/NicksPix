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
	Color m_color1, m_color2;
	int X1, Y1, X2, Y2;
	float W1, W2;
	float Z1, Z2;
	float U1, U2;
	float V1, V2;
	Edge(const Color &color1, int x1, int y1, float z1, float u1, float v1, float w1,
		 const Color &color2, int x2, int y2, float z2, float u2, float v2, float w2);
	Edge(){};
	~Edge(void){};
};// end of class Edge