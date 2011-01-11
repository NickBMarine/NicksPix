#include "Gradients.h"

Gradients::Gradients(vector<Vertex> vertices, int sides)
{
	if ( sides < 3)
		return;

	for (int i = 0; i < 3; i++)
	{
		_aOneOverW[i] = vertices[i].w;
		_aUoverW[i] = vertices[i].u;
		_aVoverW[i] = vertices[i].v;
		_aZ[i] = vertices[i].z;
	}

	float _oneOverdx = 1/ ((vertices[1].x - vertices[2].x) * (vertices[0].y - vertices[2].y) -
					(vertices[0].x - vertices[2].x) * (vertices[1].y - vertices[2].y));

	float _oneOverdy = -_oneOverdx;
	
	_dOneOverWdx = _oneOverdx * ((_aOneOverW[1] - _aOneOverW[2]) * (vertices[0].y - vertices[2].y) -
								  (_aOneOverW[0] - _aOneOverW[2]) * (vertices[1].y - vertices[2].y));
	_dOneOverWdy = _oneOverdy * ((_aOneOverW[1] - _aOneOverW[2]) * (vertices[0].x - vertices[2].x) -
								 (_aOneOverW[0] - _aOneOverW[2]) * (vertices[1].x - vertices[2].y));

	_dUoverWdx = _oneOverdx * ((_aUoverW[1] - _aUoverW[2]) * (vertices[0].y - vertices[2].y) -
								  (_aUoverW[0] - _aUoverW[2]) * (vertices[1].y - vertices[2].y));
	_dUoverWdy = _oneOverdy * ((_aUoverW[1] - _aUoverW[2]) * (vertices[0].x - vertices[2].x) -
								 (_aUoverW[0] - _aUoverW[2]) * (vertices[1].x - vertices[2].y));

	_dVoverWdx = _oneOverdx * ((_aVoverW[1] - _aVoverW[2]) * (vertices[0].y - vertices[2].y) -
								  (_aVoverW[0] - _aVoverW[2]) * (vertices[1].y - vertices[2].y));
	_dVoverWdy = _oneOverdy * ((_aUoverW[1] - _aVoverW[2]) * (vertices[0].x - vertices[2].x) -
								 (_aVoverW[0] - _aVoverW[2]) * (vertices[1].x - vertices[2].y));

	_dVoverWdx = _oneOverdx * ((_aVoverW[1] - _aVoverW[2]) * (vertices[0].y - vertices[2].y) -
								  (_aVoverW[0] - _aVoverW[2]) * (vertices[1].y - vertices[2].y));
	_dVoverWdy = _oneOverdy * ((_aUoverW[1] - _aVoverW[2]) * (vertices[0].x - vertices[2].x) -
								 (_aVoverW[0] - _aVoverW[2]) * (vertices[1].x - vertices[2].y));

	_dZoverdx = _oneOverdx * ((_aZ[1] - _aZ[2]) * (vertices[0].y - vertices[2].y) -
								  (_aZ[0] - _aZ[2]) * (vertices[1].y - vertices[2].y));

	_dZoverdy = _oneOverdy * ((_aZ[1] - _aZ[2]) * (vertices[0].x - vertices[2].x) -
								 (_aZ[0] - _aZ[2]) * (vertices[1].x - vertices[2].y));

}

Gradients::Gradients()
{
	for(int i = 0; i < 3; i++)
	{
		_aOneOverW[i] = 0;
		_aUoverW[i] = 0;
		_aVoverW[i] = 0;
	}

	_dOneOverWdx = 0;
	_dOneOverWdy = 0;
	_dUoverWdx = 0;
	_dUoverWdy = 0;
	_dVoverWdx = 0;
	_dVoverWdy = 0;
}
