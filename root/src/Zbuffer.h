struct ZBuffer
{
public:
	bool  m_nearest;
	float m_zBuffer;
	ZBuffer() {};
	ZBuffer(float distance) : m_zBuffer(distance) {};
	bool UpdateZBuff(float Z, float near, float far);
};
//