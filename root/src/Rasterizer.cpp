#include "Rasterizer.h"
#include <windows.h>


Rasterizer::Rasterizer(const unsigned width, const unsigned height, const float degrees)
{
	int w = width;
	int h = height;
	SetFov(degrees);
	leftUBounds = new float[h];
	rightUBounds = new float[h];
	leftVBounds = new float[h];
	rightVBounds = new float[h];
	leftColor = new Color[h];
	rightColor = new Color[h];
	leftZBounds = new float[h];
	rightZBounds = new float[h];
	leftBounds = new int[h];
	rightBounds = new int[h];
	leftWBounds = new float[h];
	rightWBounds = new float[h];
	m_pixels.resize(width * height);
	m_width = w;
	m_height = h;
	ResetBounds();
	m_nearPlane = 2;
	m_farPlane  = 100;
	m_zBuff.resize(width * height);
	SetUpMatrices();
	ResetZBuff();
	basisOrigin = Vertex(0.0f, 0.0f, 0.0f);
	basisP = Vertex(Color(1.0f, 0.0f, 0.0f), 1.0f, 0.0f, 0.0f);
	basisQ = Vertex(Color(0.0f, 1.0f, 0.0f), 0.0f, 1.0f, 0.0f);
	basisR = Vertex(Color(0.0f, 0.0f, 1.0f), 0.0f, 0.0f, 1.0f);
}

void Rasterizer::DrawLine(const Vertex &vertex1, const Vertex &vertex2, Color & color)
{
	float xDiff = (vertex2.x - vertex1.x);
	float yDiff = (vertex2.y - vertex1.y);

	if (xDiff == 0.0f && yDiff == 0.0f)
	{
		if ( color == NULL)
			SetPixel(int(vertex1.x), int(vertex1.y), vertex1.z, vertex1.color);
		else
			SetPixel(int(vertex1.x), int(vertex1.y), vertex1.z, color);		
	}
	
	if ( fabs(xDiff) > fabs(yDiff) )
	{
		float xMin, xMax;

		if (vertex1.x < vertex2.x)
		{
			xMin = vertex1.x;
			xMax = vertex2.x;
		}
		else
		{
			xMin = vertex2.x;
			xMax = vertex1.x;
		}
		float slope = yDiff / xDiff;
		for ( float x = xMin; x < xMax; x += 1)
		{

			float y = vertex1.y + ((x - vertex1.x) * slope);
			float z = vertex1.z + ((x - vertex1.x) * (vertex2.z - vertex1.z)/ xDiff);
			Color tempColor = vertex1.color + ((vertex2.color - vertex1.color) * ((x - vertex1.x) / xDiff));
			if ( color == NULL)
				SetPixel(int(x), int(y), z, tempColor);
			else
				SetPixel(int(x), int(y), z, color);
		}
	}
	else
	{
		float yMin, yMax;

		if (vertex1.y < vertex2.y)
		{
			yMin = vertex1.y;
			yMax = vertex2.y;
		}
		else
		{
			yMin = vertex2.y;
			yMax = vertex1.y;
		}
		float slope = xDiff / yDiff;
		for ( float y = yMin; y < yMax; y += 1)
		{
			float x = vertex1.x + ((y - vertex1.y) * slope);
			float z = vertex1.z + ((y - vertex1.y) * (vertex2.z - vertex1.z)/ yDiff);
			Color tempColor = vertex1.color + ((vertex2.color - vertex1.color) * ((y - vertex1.y) / yDiff));
			if ( color == NULL)
				SetPixel(int(x), int(y), z, tempColor);
			else
				SetPixel(int(x), int(y), z, color);
		}
	}
}

void Rasterizer::DrawSpan(const Span &span, int y)
{
	float xDiff = span.X2 - span.X1;
    if(xDiff == 0) 
		return;

	float zResult = span.Z1;
	float wInvResult = span.W1;
	float uResult = span.U1;
	float vResult = span.V1;
	float u;
	float v;

    for(int x = (span.X1); x < (span.X2); x++) 
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
	void * mem = &m_pixels[0];
	int size = m_pixels.size() * sizeof(m_pixels[0]);
 
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
			verts.push_back(Vertex(newVertices[indices[j]].x, newVertices[indices[j]].y, newVertices[indices[j]].z, newVertices[indices[j]].u, newVertices[indices[j]].v));
			verts.push_back(Vertex(newVertices[indices[j+1]].x, newVertices[indices[j+1]].y, newVertices[indices[j+1]].z, newVertices[indices[j+1]].u, newVertices[indices[j+1]].v));
			verts.push_back(Vertex(newVertices[indices[j+2]].x, newVertices[indices[j+2]].y, newVertices[indices[j+2]].z, newVertices[indices[j+2]].u, newVertices[indices[j+2]].v));

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

	Vertex camToPoly = vertices[0] - cameraPos;

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
		tempVerts[i].w = 1.0f/tempVerts[i].w;
		tempVerts[i].x *= tempVerts[i].w;
		tempVerts[i].y *= tempVerts[i].w;
		tempVerts[i].u *= tempVerts[i].w;
		tempVerts[i].v *= tempVerts[i].w;
		viewPortMatrix.Transformation(tempVerts[i]);
	}
	_gradient = Gradients(tempVerts, poly.GetSides());
	poly.SetVertices(tempVerts);

	return poly;
}

void Rasterizer::ProjectVerts(vector<Vertex> & verts)
{
	for(unsigned int i = 0; i < 3; i++)
	{
		cameraMatrix.Transformation(verts[i]);
		projMatrix.Transformation(verts[i]);
	}
}

void Rasterizer::SetFov(float Degree)
{
	m_fov = float(Degree) * (float(PI)/180.0f); 
}

void Rasterizer::SetPixel(int x, int y, float z, const Color &color)
{
	if ( x == m_width || y == m_height)
	{
		x = m_width - 1;
		y = m_height - 1;
	}

	int unsigned index = 0;
	index = (int)x + ((int)y * m_width);
	if (UpdateZBuff(z, m_nearPlane, m_farPlane, index))
	{
		m_pixels[index] = Pixel(color.r,color.g,color.b);
	}
}

void Rasterizer::SetPixel(int x, int y, float z, float u, float v)
{
	int unsigned index = 0;

	index = x + (y * m_width);

	if (UpdateZBuff(z, m_nearPlane, m_farPlane, index))
	{
		_image.SetTex(m_pixels[index], u, v);
	}
}

void Rasterizer::ResetZBuff()
{
	void * zBuff16Bit = &m_zBuff[0];
	int size = sizeof(m_zBuff[0]) * (m_width * m_height);
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
	float tempBuff = (Z - m_nearPlane)/(m_farPlane - m_nearPlane);
	if ( (tempBuff <= ConvertToFloat(m_zBuff[index])) && (tempBuff > 0.0f))
	{
		m_zBuff[index] = ConvertTo16Bit(tempBuff);
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
			cameras[i].GetCameraMatrix(cameraMatrix, cameraPos);
		}
		else 
		{
			i++;
		}
	}
}

void Rasterizer::SnagCamera(Camera& camera)
{
	camera.GetCameraMatrix(cameraMatrix, cameraPos);
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
		int yDiff = e[i].Y2 - e[i].Y1;
		if ( yDiff == 0)
			continue;
		Color colorDiff = e[i].m_color2 - e[i].m_color1;
		float xDiff = float(e[i].X2) - float(e[i].X1);
		float xStep = xDiff/yDiff;
		float zDiff = e[i].Z2 - e[i].Z1;
		float uDiff = e[i].U2 - e[i].U1;
		float vDiff = e[i].V2 - e[i].V1;
		float invWDiff = e[i].W2 - e[i].W1;
		float zStep = zDiff/yDiff;
		float uStep = uDiff/yDiff;
		float vStep = vDiff/yDiff;
		float invWStep = invWDiff/yDiff;
		float xResult = e[i].X1;
		float zResult = e[i].Z1;
		float uResult = e[i].U1;
		float vResult = e[i].V1;
		float invWResult = e[i].W1;
		Color colorResult;
		for(int j = e[i].Y1; j < e[i].Y2; j++)
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
	if ( xBounds < leftBounds[yPos] )
	{
		leftUBounds[yPos] = uBounds;
		leftVBounds[yPos] = vBounds;
		leftColor[yPos] = colorBounds;
		leftZBounds[yPos] = zBounds;
		leftWBounds[yPos] = wBounds;
	}
	leftBounds[yPos] = min(leftBounds[yPos], xBounds);

	if ( xBounds > rightBounds[yPos] )
	{
		rightUBounds[yPos] = uBounds;
		rightVBounds[yPos] = vBounds;
		rightColor[yPos] = colorBounds;
		rightZBounds[yPos] = zBounds;
		rightWBounds[yPos] = wBounds;
	}
	rightBounds[yPos] = max(rightBounds[yPos], xBounds);
}

void Rasterizer::ResetBounds()
{
	for (int i = 0; i < m_height; i++)
	{
		leftBounds[i] = (m_width + 1);
	}
	for (int i = 0; i < m_height; i++)
	{
		rightBounds[i] = (-1);
	}
}

void Rasterizer::DrawSpanBetweenBuffers()
{
	for ( int i = 0; i < m_height; i++)
	{
		if ( leftBounds[i] == (m_width + 1) && rightBounds[i] == -1 )
		{
			continue;
		}
		Span spans(leftColor[i], leftBounds[i], leftZBounds[i], leftUBounds[i], leftVBounds[i], leftWBounds[i], 
			rightColor[i], rightBounds[i], rightZBounds[i], rightUBounds[i], rightVBounds[i], rightWBounds[i]);
		DrawSpan(spans, i);
	}
}

void Rasterizer::SetUpMatrices()
{
	float h = 1/tan(m_fov/2);
	float w = h;
	float a = (float)m_width/(float)m_height;
	float z1 = m_farPlane/(m_farPlane - m_nearPlane);
	float z2 = -(m_nearPlane * m_farPlane)/(m_farPlane - m_nearPlane);
	 
	projMatrix.SetMatrix(   h,  0.0f, 0.0f,  0.0f,
						 0.0f, w * a, 0.0f,  0.0f,
						 0.0f,  0.0f,   z1,  1.0f,
						 0.0f,  0.0f,   z2,  0.0f);
	
	viewPortMatrix.SetMatrix(    float(m_width/2),                 0.0f,  0.0f, 0.0f,
							                 0.0f, float(-m_height/2),  0.0f, 0.0f,
							                 0.0f,                 0.0f,  1.0f, 0.0f,
							 float((m_width)/2), float((m_height)/2), 0.0f, 1.0f);
}