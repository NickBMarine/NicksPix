#include "Gradients.h"

Gradients::Gradients(vector<Vertex> vertices, int sides)
{
	if ( sides < 3)
		return;

	for (int i = 0; i < 3; i++)
	{
		_aOneOverW[i] = vertices[i]._w;
		_aUoverW[i] = vertices[i]._u;
		_aVoverW[i] = vertices[i]._v;
		_aZ[i] = vertices[i]._z;
	}

	float _oneOverdx = 1/ ((vertices[1]._x - vertices[2]._x) * (vertices[0]._y - vertices[2]._y) -
					(vertices[0]._x - vertices[2]._x) * (vertices[1]._y - vertices[2]._y));

	float _oneOverdy = -_oneOverdx;
	
	_dOneOverWdx = _oneOverdx * ((_aOneOverW[1] - _aOneOverW[2]) * (vertices[0]._y - vertices[2]._y) -
								  (_aOneOverW[0] - _aOneOverW[2]) * (vertices[1]._y - vertices[2]._y));
	_dOneOverWdy = _oneOverdy * ((_aOneOverW[1] - _aOneOverW[2]) * (vertices[0]._x - vertices[2]._x) -
								 (_aOneOverW[0] - _aOneOverW[2]) * (vertices[1]._x - vertices[2]._y));

	_dUoverWdx = _oneOverdx * ((_aUoverW[1] - _aUoverW[2]) * (vertices[0]._y - vertices[2]._y) -
								  (_aUoverW[0] - _aUoverW[2]) * (vertices[1]._y - vertices[2]._y));
	_dUoverWdy = _oneOverdy * ((_aUoverW[1] - _aUoverW[2]) * (vertices[0]._x - vertices[2]._x) -
								 (_aUoverW[0] - _aUoverW[2]) * (vertices[1]._x - vertices[2]._y));

	_dVoverWdx = _oneOverdx * ((_aVoverW[1] - _aVoverW[2]) * (vertices[0]._y - vertices[2]._y) -
								  (_aVoverW[0] - _aVoverW[2]) * (vertices[1]._y - vertices[2]._y));
	_dVoverWdy = _oneOverdy * ((_aUoverW[1] - _aVoverW[2]) * (vertices[0]._x - vertices[2]._x) -
								 (_aVoverW[0] - _aVoverW[2]) * (vertices[1]._x - vertices[2]._y));

	_dVoverWdx = _oneOverdx * ((_aVoverW[1] - _aVoverW[2]) * (vertices[0]._y - vertices[2]._y) -
								  (_aVoverW[0] - _aVoverW[2]) * (vertices[1]._y - vertices[2]._y));
	_dVoverWdy = _oneOverdy * ((_aUoverW[1] - _aVoverW[2]) * (vertices[0]._x - vertices[2]._x) -
								 (_aVoverW[0] - _aVoverW[2]) * (vertices[1]._x - vertices[2]._y));

	_dZoverdx = _oneOverdx * ((_aZ[1] - _aZ[2]) * (vertices[0]._y - vertices[2]._y) -
								  (_aZ[0] - _aZ[2]) * (vertices[1]._y - vertices[2]._y));

	_dZoverdy = _oneOverdy * ((_aZ[1] - _aZ[2]) * (vertices[0]._x - vertices[2]._x) -
								 (_aZ[0] - _aZ[2]) * (vertices[1]._x - vertices[2]._y));

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
