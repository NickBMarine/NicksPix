#include "Clipper.h"


Clipper::Clipper(NPolygon poly)
{
	_clipPoly = poly;
	SetBoundaries();
	SetBinaryOuts();
}

void Clipper::SetBoundaries()
{
	_B[0] = Vertex(1.0f,  0.0f, 0.0f, 1.0f);
	_B[1] = Vertex(-1.0f, 0.0f, 0.0f, 1.0f);
	_B[2] = Vertex(0.0f,  1.0f, 0.0f, 1.0f);
	_B[3] = Vertex(0.0f, -1.0f, 0.0f, 1.0f);
	_B[4] = Vertex(0.0f,  0.0f, 1.0,  0.0f);
	_B[5] = Vertex(0.0f,  0.0f, -1.0f, 1.0f);
}

void Clipper::SetBinaryOuts()
{
	float f;
	float * fx = &f;
	unsigned int * fxt = (unsigned int*)fx;

	for (int i = 0; i < 5; i++)
	{
		_biB[i] = *fxt;
	}

	_biP[0] = *fxt;
	_biP[1] = *fxt;

	_biB[0] = 0x20;
	_biB[1] = 0x10;
	_biB[2] = 0x08;
	_biB[3] = 0x04;
	_biB[4] = 0x02;
	_biB[5] = 0x01;

	_biP[0] = 0x00;
	_biP[1] = 0x00;
}

void Clipper::ResetBinaries()
{
	_biP[0] = 0x00;
	_biP[1] = 0x00;
}

NPolygon Clipper::GetClippedPoly()
{
	CycleBounds();
	
	_clipPoly.DiscardExtras();
	return _clipPoly;
}

Vertex Clipper::ComputeVert(Vertex P0, Vertex P1, 
						    Vertex boundary)
{
	float u;
	Vertex diffVert;
	float BC0;
	float BC1;
	Vertex tempVert;
	diffVert = P1.SubtractHom(P0);
	BC0 = P0.GetDotHom(boundary);
	BC1 = P1.GetDotHom(boundary);
	u = (BC0/(BC0 - BC1));
	tempVert = P0 + (diffVert * u);

	return tempVert;
}

void Clipper::CycleBounds()
{
	NPolygon t;
	for ( int i = 0; i < 5; i++)
	{
		_clipPoly.DiscardExtras();
		t.ClearPoly();
		t = _clipPoly;
		_clipPoly.ClearPoly();
		int sides = t.GetSides();
		for (int j = 0; j < sides; j++)
		{
			if (t._vertices[j].GetDotHom(_B[i]) < 0)
			{
				_biP[0] += _biB[i];
			}
			if (t._vertices[(j+1)%sides].GetDotHom(_B[i]) < 0)
			{
				_biP[1] += _biB[i];
			}
			if ((_biP[0] | _biP[1]) == 0x00)
			{
				_clipPoly.AddPoint(t._vertices[j]);
				_clipPoly.AddPoint(t._vertices[(j+1)%sides]);
			}
			if ((_biP[0] & _biP[1]) == 0x00)
			{
				Vertex tempVerts;
				if ( _biP[0] != 0x00)
				{
					tempVerts = ComputeVert(t._vertices[j], t._vertices[(j+1)%sides], _B[i]);
					_clipPoly.AddPoint(tempVerts);
					_clipPoly.AddPoint(t._vertices[(j+1)%sides]);
				}
				if ( _biP[1] != 0x00)
				{
					tempVerts = ComputeVert(t._vertices[(j+1)%sides], t._vertices[j], _B[i]);
					_clipPoly.AddPoint(t._vertices[j]);
					_clipPoly.AddPoint(tempVerts);
				}
			}
			ResetBinaries();
		}
	}
}



