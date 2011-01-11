#pragma once
#include "NPolygon.h"
#include "Vertex.h"
class Clipper
{
	Vertex _B[6];

	NPolygon _clipPoly;

	unsigned _biB[6];
	unsigned _biP[2];
public:
	Clipper () {};
	Clipper(NPolygon poly);
	void SetBoundaries();
	void SetBinaryOuts();
	void ResetBinaries();
	void GetLine();
	Vertex FindBoundary(unsigned int & boundary);
	void CycleBounds();
	NPolygon GetClippedPoly();
	Vertex ComputeVert(Vertex _P0, Vertex _P1, 
					   Vertex boundary);
	~Clipper(void){};
};

