#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Color.h"
#include "Vertex.h"
using namespace std;
class CObject
{
	fstream _mesh;
	vector<Vertex> _vertices;
	vector<unsigned short> _indices;
	void CreateMesh();
	void FileFailure(char*);
public:
	CObject(){};
	CObject(char ind_File[]);
	~CObject(void){};

	vector<Vertex> GetVertices();
	vector<unsigned short> GetIndices();
};

