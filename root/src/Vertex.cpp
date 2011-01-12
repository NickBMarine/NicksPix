#include "Vertex.h"
#include "math.h"

#define PI 3.14159265358

void Vertex::Normalize()
{
	Vertex tempVertex(_color, _x, _y, _z);
	float sqrdValues = (_x * _x) + (_y * _y) + (_z * _z);
	tempVertex._x = (tempVertex._x/sqrt(sqrdValues));
	tempVertex._y = (tempVertex._y/sqrt(sqrdValues));
	tempVertex._z = (tempVertex._z/sqrt(sqrdValues));

	*this = tempVertex;
}

Vertex Vertex::operator*(float & scalar)
{
	Vertex tempVec;

	tempVec._color = _color * scalar;
	tempVec._x = _x * scalar;
	tempVec._y = _y * scalar;
	tempVec._z = _z * scalar;
	tempVec._w = _w * scalar;
	tempVec._u = _u * scalar;
	tempVec._v = _v * scalar;

	return tempVec;
}

void Vertex::SetVec(float & X, float & Y, float & Z)
{
	_x = X;
	_y = Y;
	_z = Z;
}

Vertex Vertex::GetNormal(const Vertex & verts)
{
	Vertex normal;

	normal._x = ((_y * verts._z) - (_z * verts._y));
	normal._y = ((_z * verts._x) - (_x * verts._z));
	normal._z = ((_x * verts._y) - (_y * verts._x));

	normal.Normalize();

	return normal;
}

float Vertex::GetDotProduct(const Vertex * verts)
{
	float dot = ((_x * verts->_x) + (_y * verts->_y) + (_z * verts->_z));
	return dot;
}

float Vertex::GetDotProduct(const Vertex & verts)
{
	float dot = ((_x * verts._x) + (_y * verts._y) + (_z * verts._z));
	return dot;
}

float Vertex::GetDotHom(Vertex & verts)
{
	float dot = (verts._w * _w) + (verts._x * _x) + (verts._y * _y) + (verts._z * _z);
	return dot;
}

Vertex Vertex::SubtractHom(Vertex & verts)
{
	Vertex tempVert;

	tempVert._color = _color - verts._color;
	tempVert._x = _x - verts._x;
	tempVert._y = _y - verts._y;
	tempVert._z = _z - verts._z;
	tempVert._w = _w - verts._w;
	tempVert._u = _u - verts._u;
	tempVert._v = _v - verts._v;

	return tempVert;
}

Vertex Vertex::AddHom(Vertex & verts)
{
	Vertex tempVert;

	tempVert._color = _color + verts._color;
	tempVert._x = _x + verts._x;
	tempVert._y = _y + verts._y;
	tempVert._z = _z + verts._z;
	tempVert._w = _w + verts._w;

	return tempVert;
}

Vertex Vertex::ScaleHom(float & scale)
{
	Vertex tempVert;

	tempVert._color = _color * scale;
	tempVert._x = _x * scale;
	tempVert._y = _y * scale;
	tempVert._z = _z * scale;
	tempVert._w = _w * scale;

	return tempVert;
}

void Vertex::SetHomVec(Vertex & vec)
{
	_x = vec._x;
	_y = vec._y;
	_z = vec._z;
	_w = vec._w;
}


float Vertex::GetMagnitude()
{
	return (sqrt((_x * _x) + (_y * _y) + (_z * _z)));
}

Vertex Vertex::operator-(Vertex & vector)
{
	Vertex tempVec(_color, _x, _y, _z);
	tempVec._x = _x - vector._x;
	tempVec._y = _y - vector._y;
	tempVec._z = _z - vector._z;

	return tempVec;
}

Vertex Vertex::operator-=(Vertex & vector)
{
	_x = _x - vector._x;
	_y = _y - vector._y;
	_z = _z - vector._z;

	return *this;
}

Vertex Vertex::operator+(Vertex & vector)
{
	Vertex tempVec(_color, _x, _y, _z);
	tempVec._color = _color + vector._color;
	tempVec._x = _x + vector._x;
	tempVec._y = _y + vector._y;
	tempVec._z = _z + vector._z;
	tempVec._w = _w + vector._w;
	tempVec._u = _u + vector._u;
	tempVec._v = _v + vector._v;

	return tempVec;
}

Vertex Vertex::operator+=(Vertex & vector)
{
	_x = _x + vector._x;
	_y = _y + vector._y;
	_z = _z + vector._z;

	return *this;
}

bool Vertex::operator!=(const Vertex & vector)
{
	return ( (_x != vector._x) || (_y != vector._y) || (_z != vector._z));
}

bool Vertex::operator==(const Vertex & vector)
{
	return (( _x == vector._x) && (_y == vector._y) && (_z == vector._z));
}


void Vertex::Negate()
{
	_x = -_x;
	_y = -_y;
	_z = -_z;
}