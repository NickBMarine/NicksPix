struct ZBuffer
{
	bool  _nearest;
	float _zBuffer;
	ZBuffer() {};
	ZBuffer(float distance) : _zBuffer(distance) {};
	bool UpdateZBuff(float Z, float near, float far);
};
//