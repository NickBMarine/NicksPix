#pragma once
#include "Color.h"

struct Vertex
{
	Color _color;
	float _x, _y, _z, _w;
	float _u, _v;
	Vertex() : _x(0.0f), _y(0.0f), _z(0.0f), _u(0.0f), _v(0.0f) {};
	Vertex(const float &X, const float &Y, const float &Z) : _x(X), _y(Y), _z(Z) {};
	Vertex(const float &X, const float &Y, const float &Z, const float &U, const float &V) : _x(X), _y(Y), _z(Z), _w(1.0f), _u(U), _v(V) {};
	Vertex(const Color &C, const float &X, const float &Y) : _color(C), _x(X), _y(Y), _z(0.0f), _w(1.0f) {};
	Vertex(const Color &C, const float &X, const float &Y, const float &Z) : _color(C), _x(X), _y(Y), _z(Z), _w(1.0f){}
	Vertex(const Color &C, const float &X, const float &Y, const float &Z, const float &W) : _color(C), _x(X), _y(Y), _z(Z), _w(W){}
	Vertex(const float &X, const float &Y, const float &Z, const float &W) : _x(X), _y(Y), _z(Z), _w(W){};
	Vertex(const float &X, const float &Y, const float &Z, const float &W, const float &U, const float &V) : _x(X), _y(Y), _z(Z), _w(W), _u(U), _v(V) {};
	Vertex(const Color &C) : _color(C){};
	Vertex(const float &X) : _x(X){};
	void SetHomVec(Vertex & vector);
	void Negate();
	void Normalize();
	Vertex GetNormal(const Vertex & vect);
	float GetMagnitude();
	float GetAngleBetween(const Vertex & vect);
	float GetDotProduct(const Vertex * vect);
	float GetDotProduct(const Vertex & vect);
	float GetDotHom(Vertex & vect);
	Vertex SubtractHom(Vertex & vector);
	Vertex AddHom(Vertex & vector);
	Vertex ScaleHom(float & scale);
	Vertex operator-(Vertex & vector);
	Vertex operator-=(Vertex & vector);
	Vertex operator*(float & scalar);
	Vertex operator+(Vertex & vector);
	Vertex operator+=(Vertex & vector);
	bool operator!=(const Vertex & vector);
	bool operator==(const Vertex & vector);
	void SetVec(float & X, float & Y, float & Z);
};