#pragma once
#include "Edge.h"
#include "Vertex.h"

class NPolygon
{
	int _sides;
	vector<Edge> _edges;
	Vertex _normal;
	void CalculateEdges();
	void CalculateNorm();
public:
	NPolygon(){};
	NPolygon(vector<Vertex> & vertices, int sides);
	Vertex * GetNormal() { CalculateNorm(); return &_normal; };
	vector<Vertex> & GetVertices();
	vector<Edge> & GetEdges() { CalculateEdges(); return _edges; };
	vector<Vertex> _vertices;
	void DiscardExtras();
	void ClearPoly() { _vertices.clear(); _sides = 0; };
	void SetSides(int numSides);
	void SetVertices(vector<Vertex> & vertices);
	void SetVertices(vector<Vertex> & vertices, int numSides);
	void AddPoint(Vertex vert);
	void DiscardPoint(Vertex vert);
	int GetSides() { return _sides; };
	~NPolygon(void);
};

