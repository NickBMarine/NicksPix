#pragma once
#include "Color.h"

struct Vertex
{
public:
	Color color;
	float x, y, z, w;
	float u, v;
	Vertex() : x(0.0f), y(0.0f), z(0.0f), u(0.0f), v(0.0f) {};
	Vertex(const float &X, const float &Y, const float &Z) : x(X), y(Y), z(Z) {};
	Vertex(const float &X, const float &Y, const float &Z, const float &U, const float &V) : x(X), y(Y), z(Z), u(U), v(V) {};
	Vertex(const Color &C, const float &X, const float &Y) : color(C), x(X), y(Y), z(0.0f), w(1.0f) {};
	Vertex(const Color &C, const float &X, const float &Y, const float &Z) : color(C), x(X), y(Y), z(Z), w(1.0f){}
	Vertex(const Color &C, const float &X, const float &Y, const float &Z, const float &W) : color(C), x(X), y(Y), z(Z), w(W){}
	Vertex(const float &X, const float &Y, const float &Z, const float &W) : x(X), y(Y), z(Z), w(W){};
	Vertex(const float &X, const float &Y, const float &Z, const float &W, const float &U, const float &V) : x(X), y(Y), z(Z), w(W), u(U), v(V) {};
	Vertex(const Color &C) : color(C){};
	Vertex(const float &X) : x(X){};
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