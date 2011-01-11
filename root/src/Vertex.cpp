#include "Vertex.h"
#include "math.h"

#define PI 3.14159265358

void Vertex::Normalize()
{
	Vertex tempVertex(color, x, y, z);
	float sqrdValues = (x * x) + (y * y) + (z * z);
	tempVertex.x = (tempVertex.x/sqrt(sqrdValues));
	tempVertex.y = (tempVertex.y/sqrt(sqrdValues));
	tempVertex.z = (tempVertex.z/sqrt(sqrdValues));

	*this = tempVertex;
}

Vertex Vertex::operator*(float & scalar)
{
	Vertex tempVec;

	tempVec.color = color * scalar;
	tempVec.x = x * scalar;
	tempVec.y = y * scalar;
	tempVec.z = z * scalar;
	tempVec.w = w * scalar;
	tempVec.u = u * scalar;
	tempVec.v = v * scalar;

	return tempVec;
}

void Vertex::SetVec(float & X, float & Y, float & Z)
{
	x = X;
	y = Y;
	z = Z;
}

Vertex Vertex::GetNormal(const Vertex & verts)
{
	Vertex normal;

	normal.x = ((y * verts.z) - (z * verts.y));
	normal.y = ((z * verts.x) - (x * verts.z));
	normal.z = ((x * verts.y) - (y * verts.x));

	normal.Normalize();

	return normal;
}

float Vertex::GetDotProduct(const Vertex * verts)
{
	float dot = ((x * verts->x) + (y * verts->y) + (z * verts->z));
	return dot;
}

float Vertex::GetDotProduct(const Vertex & verts)
{
	float dot = ((x * verts.x) + (y * verts.y) + (z * verts.z));
	return dot;
}

float Vertex::GetDotHom(Vertex & verts)
{
	float dot = (verts.w * w) + (verts.x * x) + (verts.y * y) + (verts.z * z);
	return dot;
}

Vertex Vertex::SubtractHom(Vertex & verts)
{
	Vertex tempVert;

	tempVert.color = color - verts.color;
	tempVert.x = x - verts.x;
	tempVert.y = y - verts.y;
	tempVert.z = z - verts.z;
	tempVert.w = w - verts.w;
	tempVert.u = u - verts.u;
	tempVert.v = v - verts.v;

	return tempVert;
}

Vertex Vertex::AddHom(Vertex & verts)
{
	Vertex tempVert;

	tempVert.color = color + verts.color;
	tempVert.x = x + verts.x;
	tempVert.y = y + verts.y;
	tempVert.z = z + verts.z;
	tempVert.w = w + verts.w;

	return tempVert;
}

Vertex Vertex::ScaleHom(float & scale)
{
	Vertex tempVert;

	tempVert.color = color * scale;
	tempVert.x = x * scale;
	tempVert.y = y * scale;
	tempVert.z = z * scale;
	tempVert.w = w * scale;

	return tempVert;
}

void Vertex::SetHomVec(Vertex & vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}


float Vertex::GetMagnitude()
{
	return (sqrt((x * x) + (y * y) + (z * z)));
}

Vertex Vertex::operator-(Vertex & vector)
{
	Vertex tempVec(color, x, y, z);
	tempVec.x = x - vector.x;
	tempVec.y = y - vector.y;
	tempVec.z = z - vector.z;

	return tempVec;
}

Vertex Vertex::operator-=(Vertex & vector)
{
	x = x - vector.x;
	y = y - vector.y;
	z = z - vector.z;

	return *this;
}

Vertex Vertex::operator+(Vertex & vector)
{
	Vertex tempVec(color, x, y, z);
	tempVec.color = color + vector.color;
	tempVec.x = x + vector.x;
	tempVec.y = y + vector.y;
	tempVec.z = z + vector.z;
	tempVec.w = w + vector.w;
	tempVec.u = u + vector.u;
	tempVec.v = v + vector.v;

	return tempVec;
}

Vertex Vertex::operator+=(Vertex & vector)
{
	x = x + vector.x;
	y = y + vector.y;
	z = z + vector.z;

	return *this;
}

bool Vertex::operator!=(const Vertex & vector)
{
	return ( (x != vector.x) || (y != vector.y) || (z != vector.z));
}

bool Vertex::operator==(const Vertex & vector)
{
	return (( x == vector.x) && (y == vector.y) && (z == vector.z));
}


void Vertex::Negate()
{
	x = -x;
	y = -y;
	z = -z;
}