#pragma once
#include <assert.h>
#include "Gradients.h"
#include "Texel.h"
#include "Color.h"
#include "Edge.h"
#include "Span.h"
#include "NPolygon.h"
#include "Matrix4x4.h"
#include "Vertex.h"
#include "Zbuffer.h"
#include "Camera.h"
#include "Clipper.h"

#define PI 3.14159265358
//=== class Rasterizer ==============================================
//This is the grand father of my whole software rasterizer project. 
//This collects information about the pixels, maps them and creates
//different transformations using other classes. 
//===================================================================
class Rasterizer
{
private:
	//Store the width and height of the display and the pixels.
	Display _display;
	Gradients _gradient;
	Color * _leftColor;
	Color * _rightColor;
	Vertex _basisOrigin;
	Vertex _basisP;
	Vertex _basisQ;
	Vertex _basisR;
	float * _leftUBounds;
	float * _rightUBounds;
	float * _leftVBounds;
	float * _rightVBounds;
	float * _leftZBounds;
	float * _rightZBounds;
	float * _leftWBounds;
	float * _rightWBounds;
	int * _leftBounds;
	int * _rightBounds;
	vector<Pixel> _pixels;
	vector<unsigned short> _zBuff;
	Vertex _cameraPos;
	Texel _image;
	bool _texMap;
	bool _doGradients;
	bool _drawBasis;
	Matrix4x4 _cameraMatrix;
	Matrix4x4 _projMatrix;
	Matrix4x4 _screenMatrix;
	Matrix4x4 _toClipMatrix;
	Matrix4x4 _invClipMatrix;
	Matrix4x4 _viewPortMatrix;
	int _width, _height;
	int _rotManager;
	float _fov,
		  _projFacto;
	float _nearPlane,
		  _farPlane;
public:
	Rasterizer(){};
	Rasterizer(const unsigned int width, const unsigned int height, const float Degrees);
	~Rasterizer(){};

	//Sets individual pixels according to the x and y values introduced.
	void SetPixel(int x, int y, float z, const Color &color);
	//Added implementation for texels
	void SetPixel(int x, int y, float z, float u, float v);
	//Returns the object's m_pixels data member.
	vector<Pixel> & GetPixels() {ResetZBuff(); return _pixels;};
	//Draws a line
	void DrawLine(const Vertex &vertex1, const Vertex &vertex2, Color & color = Color(1.0f, 0.0f, 0.0f));
	//Draws a triangle. Last argument uses a bool value to either fill
	//the triangle or to keep it empty. Default is set to false.
	void DrawTriangle(NPolygon poly, const bool FILL = false);
	//Draws a Polygon
	void DrawPolygon(NPolygon poly);
	//Draws the spans between edges in a triangle.
	void DrawSpanBetweenEdges(const Edge &e1, const Edge &e2);
	//Draws the spans between buffers in a polygon
	void DrawSpanBetweenBuffers();
	//Defines Color and Z bounds
	void DefineBounds(Edge e[], int numEdges);
	//Draws each span individually.
	void DrawSpan(const Span &span, int y);
	//Clears the screen each time it is called.
	void ClearScreen();
	//Set the FOV
	void SetFov(float Degree);
	//Set the image buffer
	void SetText(Texel & image) { _image = image; _texMap = true; };
	//Is this textured?
	bool IsText() { return _texMap;}
	//Convert vertices to screen coordinates and then use them with indices
	void ProcessVertices(const vector<Vertex> & vertices, 
						 const vector<unsigned short> & indices, 
						 const Matrix4x4 & worldMatrix,
						 bool fill);
	//Convert vertices to screen coordinates with texture
	void ProcessVertices(const vector<Vertex> & vertices, 
						 const vector<unsigned short> & indices, 
						 const Matrix4x4 & worldMatrix);
	//Reset the Z Buffer
	void ResetZBuff();
	//Grab the Camera
	void SnagCamera(Camera cameras[]);
	void SnagCamera(Camera & camera);
	//Check for culling
	bool CullCheck(NPolygon poly);
	//Project
	void ProjectVerts(vector<Vertex> & verts);
	//Converts Degrees to Radians
	float ToRadians(float degrees);
	//Find the low and high values of the edges
	void CheckEdges(vector<Edge> & e, unsigned short numEdges);
	//Assign left and right buffer
	void GetBuffer(int xBounds, float zBounds, float uBounds, float vBounds, float wBounds, Color colorBounds, int yPos);
	//Reset left and right bounds
	void ResetBounds();
	//Clipper
	NPolygon ClipCheck(vector<Vertex> & verts);
	//Create matrices
	void SetUpMatrices();
	//Update the ZBuffer
	bool UpdateZBuff(float Z, float near, float far, int index);
	//Converts float to 16bit
	float ConvertTo16Bit(float & tempFloat);
	//Converts 16bit to float
	float ConvertToFloat(unsigned short & temp16Bit);
	//Do we want to draw basis vectors?
	void DoBasis(bool basis)
	{
		_drawBasis = basis;
	}

	void DrawBasis();
}; // end of class Rasterizer


