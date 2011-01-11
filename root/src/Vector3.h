#pragma once
#include <math.h>
class Vector3
{
public:
	float x, y, z;
	// copy constructor
	Vector3();
	Vector3(const Vector3 &a) : x(a.x), y(a.y), z(a.z){};
	// initialization by three float values
	Vector3(float nx, float ny, float nz) : x(nx), y(ny), z(nz){};
	// assignment operation
	Vector3 &operator=(const Vector3 &a);
	// test for equality operators
	bool operator==(const Vector3 &a) const;
	bool operator!=(const Vector3 &a) const;
// Vector operations
	// set the vector to zero
	void zero() { x = y = z = 0.0f;};
	// minus returns the negative of the vector
	Vector3 operator-() const { return Vector3(-x,-y,-z);};
	// Add and subtract vectors
	Vector3 operator-(const Vector3 &a) const;
	Vector3 operator+(const Vector3 &a) const;
	// Multiplication and division by scalar
	Vector3 operator*(float a) const;
	Vector3 operator/(float a) const;
	// Combined assignment operator
	Vector3 &operator+=(const Vector3 &a);
	Vector3 &operator-=(const Vector3 &a);
	Vector3 &operator*=(float k);
	Vector3 &operator/=(float k);
	// Normalize the vector
	void normalize();
	float operator*(const Vector3 &a) const;
	~Vector3(void);
};

