#include "NPolygon.h"


NPolygon::NPolygon(vector<Vertex> & vertices, 
				   int sides)
{
	_sides = sides;
	for (int i = 0; i < sides; i++)
	{
		_vertices.push_back(vertices[i]);
	}
}


NPolygon::~NPolygon(void)
{
}

vector<Vertex> & NPolygon::GetVertices()
{
	return _vertices;
}

void NPolygon::CalculateEdges()
{
	for ( int i = 0; i < _sides; i++)
	{
		_edges.push_back(Edge(_vertices[i].color, _vertices[i].x, _vertices[i].y, _vertices[i].z, _vertices[i].u, _vertices[i].v, 
			_vertices[i].w, _vertices[(i+1)%_sides].color, _vertices[(i+1)%_sides].x, _vertices[(i+1)%_sides].y, _vertices[(i+1)%_sides].z, 
			_vertices[(i+1)%_sides].u, _vertices[(i+1)%_sides].v, _vertices[(i+1)%_sides].w));
	}
}

void NPolygon::CalculateNorm()
{
	Vertex e3 = _vertices[1] - _vertices[0];
	Vertex e1 = _vertices[2] - _vertices[1];
	_normal = e3.GetNormal(e1);
}

void NPolygon::AddPoint(Vertex vert)
{
	for ( int i = 0; i < _sides; i++)
	{
		if ( vert == _vertices[i] )
		{
			return;
		}
	}
	_sides++;

	_vertices.push_back(vert);
}

void NPolygon::SetVertices(vector<Vertex> & vertices)
{
	for (int i = 0; i < _sides; i++)
	{
		_vertices[i] = vertices[i];
	}
}

void NPolygon::SetVertices(vector<Vertex> & vertices, int numSides)
{
	_sides = numSides;

	_vertices.resize(numSides);

	for (int i = 0; i < _sides; i++)
	{
		_vertices[i] = vertices[i];
	}
}

void NPolygon::SetSides(int numSides)
{
	_sides = numSides;
}

void NPolygon::DiscardExtras()
{
	for (int i = 0; i < _sides; i++)
	{
		for (int j = 0; j < _sides; j++)
		{
			if ( _vertices.size() <= 1)
				return;
			if (j == i)
			{
				j++;
			}
			if ( _vertices[i] == _vertices[j%_vertices.size()])
			{
				_vertices.erase(_vertices.begin() + j);
				_sides--;
			}
		}
	}
}