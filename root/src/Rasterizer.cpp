#include "Rasterizer.h"
#include <windows.h>


Rasterizer::Rasterizer(const unsigned width, const unsigned height, const float degrees)
{
	int w = width;
	int h = height;
	SetFov(degrees);
	_leftUBounds = new float[h];
	_rightUBounds = new float[h];
	_leftVBounds = new float[h];
	_rightVBounds = new float[h];
	_leftColor = new Color[h];
	_rightColor = new Color[h];
	_leftZBounds = new float[h];
	_rightZBounds = new float[h];
	_leftBounds = new int[h];
	_rightBounds = new int[h];
	_leftWBounds = new float[h];
	_rightWBounds = new float[h];
	_pixels.resize(width * height);
	_width = w;
	_height = h;
	ResetBounds();
	_nearPlane = 2;
	_farPlane  = 100;
	_zBuff.resize(width * height);
	SetUpMatrices();
	ResetZBuff();
	_basisOrigin = Vertex(0.0f, 0.0f, 0.0f);
	_basisP = Vertex(Color(1.0f, 0.0f, 0.0f), 1.0f, 0.0f, 0.0f);
	_basisQ = Vertex(Color(0.0f, 1.0f, 0.0f), 0.0f, 1.0f, 0.0f);
	_basisR = Vertex(Color(0.0f, 0.0f, 1.0f), 0.0f, 0.0f, 1.0f);
}

void Rasterizer::DrawLine(const Vertex &vertex1, const Vertex &vertex2, Color & color)
{
	float xDiff = (vertex2._x - vertex1._x);
	float yDiff = (vertex2._y - vertex1._y);

	if (xDiff == 0.0f && yDiff == 0.0f)
	{
		if ( color == NULL)
			SetPixel(int(vertex1._x), int(vertex1._y), vertex1._z, vertex1._color);
		else
			SetPixel(int(vertex1._x), int(vertex1._y), vertex1._z, color);		
	}
	
	if ( fabs(xDiff) > fabs(yDiff) )
	{
		float xMin, xMax;

		if (vertex1._x < vertex2._x)
		{
			xMin = vertex1._x;
			xMax = vertex2._x;
		}
		else
		{
			xMin = vertex2._x;
			xMax = vertex1._x;
		}
		float slope = yDiff / xDiff;
		for ( float x = xMin; x < xMax; x += 1)
		{

			float y = vertex1._y + ((x - vertex1._x) * slope);
			float z = vertex1._z + ((x - vertex1._x) * (vertex2._z - vertex1._z)/ xDiff);
			Color tempColor = vertex1._color + ((vertex2._color - vertex1._color) * ((x - vertex1._x) / xDiff));
			if ( color == NULL)
				SetPixel(int(x), int(y), z, tempColor);
			else
				SetPixel(int(x), int(y), z, color);
		}
	}
	else
	{
		float yMin, yMax;

		if (vertex1._y < vertex2._y)
		{
			yMin = vertex1._y;
			yMax = vertex2._y;
		}
		else
		{
			yMin = vertex2._y;
			yMax = vertex1._y;
		}
		float slope = xDiff / yDiff;
		for ( float y = yMin; y < yMax; y += 1)
		{
			float x = vertex1._x + ((y - vertex1._y) * slope);
			float z = vertex1._z + ((y - vertex1._y) * (vertex2._z - vertex1._z)/ yDiff);
			Color tempColor = vertex1._color + ((vertex2._color - vertex1._color) * ((y - vertex1._y) / yDiff));
			if ( color == NULL)
				SetPixel(int(x), int(y), z, tempColor);
			else
				SetPixel(int(x), int(y), z, color);
		}
	}
}

void Rasterizer::DrawSpan(const Span &span, int y)
{
	float xDiff = span._x2 - span._x1;
    if(xDiff == 0) 
		return;

	float zResult = span._z1;
	float wInvResult = span._w1;
	float uResult = span._u1;
	float vResult = span._v1;
	float u;
	float v;

    for(int x = (span._x1); x < (span._x2); x++) 
	{
		u = uResult/wInvResult;
		v = vResult/wInvResult;
		SetPixel(x, y, zResult, u, v);
		wInvResult += _gradient._dOneOverWdx;
		uResult += _gradient._dUoverWdx;
		vResult += _gradient._dVoverWdx;
		zResult += _gradient._dZoverdx;
	}
}

void Rasterizer::ClearScreen()
{
	void * mem = &_pixels[0];
	int size = _pixels.size() * sizeof(_pixels[0]);
 
	memset(mem, 0, size);
}

void Rasterizer::ProcessVertices(const vector<Vertex> & vertices,
							   const vector<unsigned short> & indices,
							   const Matrix4x4 & worldMat,
							   bool fill) 
{
	_texMap = fill;
	vector<Vertex> newVertices(vertices);

	Matrix4x4 worldMatrix;

	worldMatrix.SetMatrix(worldMat);
	
	for ( unsigned int i = 0; i < newVertices.size(); i++)
	{
		worldMatrix.Transformation(newVertices, i);
	}

	assert((indices.size()%3)==0);

	int index = (indices.size())/3;

	int j = 0;
	
	for ( int i = 0; i < index; i++)
	{
		vector<Vertex> verts;
			verts.push_back(Vertex(newVertices[indices[j]]._x, newVertices[indices[j]]._y, newVertices[indices[j]]._z, newVertices[indices[j]]._u, newVertices[indices[j]]._v));
			verts.push_back(Vertex(newVertices[indices[j+1]]._x, newVertices[indices[j+1]]._y, newVertices[indices[j+1]]._z, newVertices[indices[j+1]]._u, newVertices[indices[j+1]]._v));
			verts.push_back(Vertex(newVertices[indices[j+2]]._x, newVertices[indices[j+2]]._y, newVertices[indices[j+2]]._z, newVertices[indices[j+2]]._u, newVertices[indices[j+2]]._v));

		NPolygon poly(verts, 3);

		if (CullCheck(poly))
		{
			DrawPolygon(poly);
		}

		j += 3;
	}
}

bool Rasterizer::CullCheck(NPolygon poly)
{
	Vertex * polyNorm = poly.GetNormal();
	vector<Vertex> vertices = poly.GetVertices();

	Vertex camToPoly = vertices[0] - _cameraPos;

	if (camToPoly.GetDotProduct(polyNorm) > 0)
	{
		return false;
	}
	else
	{
		return true;
	}

	
}

void Rasterizer::DrawPolygon(NPolygon poly)
{
	int sides;
	vector<Vertex> vertices = poly.GetVertices();
	NPolygon polex;
	if ( _texMap )
	{
		ProjectVerts(vertices);
		polex = ClipCheck(vertices);
		vector<Edge> edges = polex.GetEdges();
		sides = polex.GetSides();
		if ( sides == 0)
			return;
		CheckEdges(edges , sides);
		DrawSpanBetweenBuffers();
		ResetBounds();
	}
	else
	{
		ProjectVerts(vertices);
		polex = ClipCheck(vertices);
		sides = polex.GetSides();
		vertices = polex.GetVertices();
		if ( sides == 0)
			return;
		for(int i = 0; i < sides; i++)
		{
			DrawLine(vertices[i], vertices[(i+1)%sides]);
		}
	}

}

NPolygon Rasterizer::ClipCheck(vector<Vertex> & verts)
{
	NPolygon poly(verts, 3);

	Clipper clip(poly);

	poly.ClearPoly();

	poly = clip.GetClippedPoly();
	vector<Vertex> tempVerts = poly.GetVertices();
	for (int i = 0; i < poly.GetSides(); i++)
	{
		tempVerts[i]._w = 1.0f/tempVerts[i]._w;
		tempVerts[i]._x *= tempVerts[i]._w;
		tempVerts[i]._y *= tempVerts[i]._w;
		tempVerts[i]._u *= tempVerts[i]._w;
		tempVerts[i]._v *= tempVerts[i]._w;
		_viewPortMatrix.Transformation(tempVerts[i]);
	}
	_gradient = Gradients(tempVerts, poly.GetSides());
	poly.SetVertices(tempVerts);

	return poly;
}

void Rasterizer::ProjectVerts(vector<Vertex> & verts)
{
	for(unsigned int i = 0; i < 3; i++)
	{
		_cameraMatrix.Transformation(verts[i]);
		_projMatrix.Transformation(verts[i]);
	}
}

void Rasterizer::SetFov(float Degree)
{
	_fov = float(Degree) * (float(PI)/180.0f); 
}

void Rasterizer::SetPixel(int x, int y, float z, const Color &color)
{
	if ( x == _width || y == _height)
	{
		x = _width - 1;
		y = _height - 1;
	}

	int unsigned index = 0;
	index = (int)x + ((int)y * _width);
	if (UpdateZBuff(z, _nearPlane, _farPlane, index))
	{
		_pixels[index] = Pixel(color._r,color._g,color._b);
	}
}

void Rasterizer::SetPixel(int x, int y, float z, float u, float v)
{
	int unsigned index = 0;

	index = x + (y * _width);

	if (UpdateZBuff(z, _nearPlane, _farPlane, index))
	{
		_image.SetTex(_pixels[index], u, v);
	}
}

void Rasterizer::ResetZBuff()
{
	void * zBuff16Bit = &_zBuff[0];
	int size = sizeof(_zBuff[0]) * (_width * _height);
	memset(zBuff16Bit, 0xF, size);
}

float Rasterizer::ConvertToFloat(unsigned short & temp16Bit)
{
	return temp16Bit/3855.0f;
}

float Rasterizer::ConvertTo16Bit(float & tempFloat)
{
	return (3855.0f * tempFloat);
}

bool Rasterizer::UpdateZBuff(float Z, float nearZ, float farZ, int index)
{
	float tempBuff = (Z - _nearPlane)/(_farPlane - _nearPlane);
	if ( (tempBuff <= ConvertToFloat(_zBuff[index])) && (tempBuff > 0.0f))
	{
		_zBuff[index] = ConvertTo16Bit(tempBuff);
		return true;
	}
	else
	{
		return false;
	}
}

void Rasterizer::SnagCamera(Camera cameras[])
{
	for(unsigned short i = 0; i < Camera::GetNumCameras(); i++)
	{
		if (cameras[i].GetActivety())
		{
			cameras[i].GetCameraMatrix(_cameraMatrix, _cameraPos);
		}
		else 
		{
			i++;
		}
	}
}

void Rasterizer::SnagCamera(Camera& camera)
{
	camera.GetCameraMatrix(_cameraMatrix, _cameraPos);
}

float Rasterizer::ToRadians(float degrees)
{
	float radians = degrees * (float(PI)/180.0f);
	return radians;
}

void Rasterizer::CheckEdges(vector<Edge> & e, unsigned short numEdges)
{
	for (unsigned int i = 0; i < numEdges; i++)
	{
		int yDiff = e[i]._y2 - e[i]._y1;
		if ( yDiff == 0)
			continue;
		Color colorDiff = e[i]._color2 - e[i]._color1;
		float xDiff = float(e[i]._x2) - float(e[i]._x1);
		float xStep = xDiff/yDiff;
		float zDiff = e[i]._z2 - e[i]._z1;
		float uDiff = e[i]._u2 - e[i]._u1;
		float vDiff = e[i]._v2 - e[i]._v1;
		float invWDiff = e[i]._w2 - e[i]._w1;
		float zStep = zDiff/yDiff;
		float uStep = uDiff/yDiff;
		float vStep = vDiff/yDiff;
		float invWStep = invWDiff/yDiff;
		float xResult = e[i]._x1;
		float zResult = e[i]._z1;
		float uResult = e[i]._u1;
		float vResult = e[i]._v1;
		float invWResult = e[i]._w1;
		Color colorResult;
		for(int j = e[i]._y1; j < e[i]._y2; j++)
		{
			GetBuffer(int(xResult), zResult, uResult, vResult, invWResult, colorResult, j);
			xResult += xStep;
			zResult += zStep; 
			uResult += uStep;
			vResult += vStep;
			invWResult += invWStep;
		}
	}
}


void Rasterizer::GetBuffer(int xBounds, float zBounds, float uBounds, float vBounds, float wBounds, Color colorBounds, int yPos)
{
	if ( xBounds < _leftBounds[yPos] )
	{
		_leftUBounds[yPos] = uBounds;
		_leftVBounds[yPos] = vBounds;
		_leftColor[yPos] = colorBounds;
		_leftZBounds[yPos] = zBounds;
		_leftWBounds[yPos] = wBounds;
	}
	_leftBounds[yPos] = min(_leftBounds[yPos], xBounds);

	if ( xBounds > _rightBounds[yPos] )
	{
		_rightUBounds[yPos] = uBounds;
		_rightVBounds[yPos] = vBounds;
		_rightColor[yPos] = colorBounds;
		_rightZBounds[yPos] = zBounds;
		_rightWBounds[yPos] = wBounds;
	}
	_rightBounds[yPos] = max(_rightBounds[yPos], xBounds);
}

void Rasterizer::ResetBounds()
{
	for (int i = 0; i < _height; i++)
	{
		_leftBounds[i] = (_width + 1);
	}
	for (int i = 0; i < _height; i++)
	{
		_rightBounds[i] = (-1);
	}
}

void Rasterizer::DrawSpanBetweenBuffers()
{
	for ( int i = 0; i < _height; i++)
	{
		if ( _leftBounds[i] == (_width + 1) && _rightBounds[i] == -1 )
		{
			continue;
		}
		Span spans(_leftColor[i], _leftBounds[i], _leftZBounds[i], _leftUBounds[i], _leftVBounds[i], _leftWBounds[i], 
			       _rightColor[i], _rightBounds[i], _rightZBounds[i], _rightUBounds[i], _rightVBounds[i], _rightWBounds[i]);
		DrawSpan(spans, i);
	}
}

void Rasterizer::SetUpMatrices()
{
	float h = 1/tan(_fov/2);
	float w = h;
	float a = (float)_width/(float)_height;
	float z1 = _farPlane/(_farPlane - _nearPlane);
	float z2 = -(_nearPlane * _farPlane)/(_farPlane - _nearPlane);
	 
	_projMatrix.SetMatrix(   h,  0.0f, 0.0f,  0.0f,
						  0.0f, w * a, 0.0f,  0.0f,
						  0.0f,  0.0f,   z1,  1.0f,
						  0.0f,  0.0f,   z2,  0.0f);
	
	_viewPortMatrix.SetMatrix(    float(_width/2),               0.0f,  0.0f, 0.0f,
							                 0.0f,  float(-_height/2),  0.0f, 0.0f,
							                 0.0f,               0.0f,  1.0f, 0.0f,
							    float((_width)/2), float((_height)/2),  0.0f, 1.0f);
}