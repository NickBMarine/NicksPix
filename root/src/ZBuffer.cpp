#include "Zbuffer.h"

bool ZBuffer::UpdateZBuff(float Z, float nearZ, float farZ)
{
	float tempBuff = (Z - nearZ)/(farZ - nearZ);
	if ( tempBuff <= m_zBuffer && tempBuff >= 0.0f)
	{
		m_zBuffer = tempBuff;
		return true;
	}
	else
	{
		return false;
	}
}