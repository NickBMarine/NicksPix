#include "Vector3.h"

Vector3::Vector3()
{
}

Vector3::~Vector3()
{
}

Vector3 &Vector3::operator=(const Vector3 &a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	return *this;
}

bool Vector3::operator==(const Vector3 &a) const
{
	return (x==a.x && y==a.y && z==a.z);
}

bool Vector3::operator!=(const Vector3 &a) const
{
	return (x!=a.x||y!=a.y||z!=a.z);
}

Vector3 Vector3::operator-(const Vector3 &a) const
{
	return Vector3(x-a.x, y-a.y, z-a.z);
}

Vector3 Vector3::operator+(const Vector3 &a) const
{
	return Vector3(x+a.x, y+a.y, z+a.z);
}

Vector3 Vector3::operator*(float a) const
{
	return Vector3(x*a, y*a, z*a);
}

Vector3 Vector3::operator/(float a) const
{
	return Vector3(x/a, y/a, z/a);
}

Vector3 &Vector3::operator+=(const Vector3 &a) 
{
	x += a.x;
	y += a.y;
	z += a.z;
	return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	return *this;
}

Vector3 &Vector3::operator*=(float k)
{
	x *= k;
	y *= k;
	z *= k;
	return *this;
}

Vector3 &Vector3::operator/=(float k)
{
	x /= k;
	y /= k;
	z /= k;
	return *this;
}

void Vector3::normalize()
{
	float mag, magSqrd;

	magSqrd = (x*x)+(y*y)+(z*z);

	mag = sqrt(magSqrd);

	x/=mag;
	y/=mag;
	z/=mag;
}

float Vector3::operator*(const Vector3 &a) const
{
	float dotProduct;
	dotProduct = (x*a.x)+(y*a.y)+(z*a.z);
	return dotProduct;
}

inline float vectorMag(const Vector3 &a)
{
	float sqrdMag = (a.x*a.x)+(a.y*a.y)+(a.z*a.z);
	return sqrt(sqrdMag);
}

inline Vector3 crossProduct(const Vector3 &u, const Vector3 &v)
{
	return Vector3(u.y*v.z-u.z*v.y,
				   u.z*v.x-u.x*v.z,
				   u.x*v.y-u.y*v.x);
}

inline Vector3 operator*(float k, const Vector3 &u)
{
	return Vector3(u.x * k, u.y * k, u.z * k);
}
inline float distance(const Vector3 &u, const Vector3 &v)
{
	float tempX = u.x-v.x;
	float tempY = u.y-v.y;
	float tempZ = u.z-v.z;
	float sqrdMag = (tempX*tempX) + (tempY*tempY) + (tempZ*tempZ);
	return sqrt(sqrdMag);
}
