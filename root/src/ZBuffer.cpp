#include "Zbuffer.h"

bool ZBuffer::UpdateZBuff(float Z, float nearZ, float farZ)
{
	float tempBuff = (Z - nearZ)/(farZ - nearZ);
	if ( tempBuff <= _zBuffer && tempBuff >= 0.0f)
	{
		_zBuffer = tempBuff;
		return true;
	}
	else
	{
		return false;
	}
}