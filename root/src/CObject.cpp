#include "CObject.h"


CObject::CObject(char ind_file[], Color & c)
{
	_mesh.open(ind_file, ios::in);
	FileFailure(ind_file);
	_color = c;
	CreateMesh();
}

void CObject::CreateMesh()
{
	string verts, indices;
	float numVerts, numFaces;
	_mesh >> verts >> numVerts;
	_mesh >> indices >> numFaces;

	for ( int i = 0; i < numVerts; i++)
	{
		float x, y, z;
		_mesh >> x >> y >> z;
		_vertices.push_back(Vertex(_color, x, y, z));
	}



	for ( int i = 0; i < numFaces; i++)
	{
		unsigned short pt1, pt2, pt3, pt4, pt5, pt6;
		_mesh >> pt1;
		_mesh >> pt2;
		_mesh >> pt3;
		_mesh >> pt4;
		_mesh >> pt5;
		_mesh >> pt6;
		_indices.push_back(pt1);
		_indices.push_back(pt2);
		_indices.push_back(pt3);
		_indices.push_back(pt4);
		_indices.push_back(pt5);
		_indices.push_back(pt6);
	}

}

void CObject::FileFailure(char* filename)
{
	if (_mesh.fail())
	{
		cout << "File " << filename << " failed to load.\n";
		cout << "Program will close. \n";
		exit(0);
	}
}

vector<Vertex> CObject::GetVertices()
{
	return _vertices;
}

vector<unsigned short> CObject::GetIndices()
{
	return _indices;
}