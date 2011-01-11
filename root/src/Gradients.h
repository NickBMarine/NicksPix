#pragma once
#include <vector>
#include "Vertex.h"
#include "Edge.h"
using namespace std;

struct Gradients
{
	float _aUoverW[3];
	float _aVoverW[3];
	float _aOneOverW[3];
	float _aZ[3];
	float _dUoverWdy, _dUoverWdx;
	float _dVoverWdy, _dVoverWdx;
	float _dOneOverWdy, _dOneOverWdx;
	float _dZoverdy, _dZoverdx;

	Gradients();
	Gradients(vector<Vertex> vector, int sides);
	vector<Edge> & GetEdgeaUoverW();
	vector<Edge> & GetEdgeaVoverW();
	vector<Edge> & GetEdgeaOneOverW();
};