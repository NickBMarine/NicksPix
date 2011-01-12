#pragma once
#include "Rasterizer.h"
#include "NPolygon.h"
#include "Keys.h"

class GObject
{
	std::vector<NPolygon> _polygon;
	std::vector<Vertex> _verts;
	std::vector<unsigned short> _index;

	Matrix4x4 _worldMatrix;

	bool _isDirty;
	bool _isWorld;
	bool _displayBasis;
	bool _filled;

	Vertex _rot;
	Vertex _trans;
	Vertex _pos;
	Vertex _scale;
	Vertex _arbAxis;

	float _arbRot;

public:

	void InitializeVert(const std::vector<Vertex> & vertices);
	void InitializeIndices(const std::vector<unsigned short> & indiceCount);
	void Fill(bool fill);
	void SetArbAxis(Vertex & vert);

    std::vector<Vertex> * AccessVertices();        
    std::vector<unsigned short> * AccessIndices();       
 
    void Render(Rasterizer& raster);
 
	// Flags dirty 
	//====================================================================================
    void Translate(const Vertex & translate);
	void TranslateX(const float & translate);
	void TranslateY(const float & translate);
	void TranslateZ(const float & translate);
    void SetPos(const Vertex & pos);
   
	void RotateX(float degrees);
	void RotateY(float degrees);
	void RotateZ(float degrees);
 
	void ScaleX(float scalar) { if (scalar != _scale._x) { _isDirty = true; _scale._x = scalar; } } ;
	void ScaleY(float scalar) { if (scalar != _scale._y) { _isDirty = true; _scale._y = scalar; } } ;
	void ScaleZ(float scalar) { if (scalar != _scale._z) { _isDirty = true; _scale._z = scalar; } } ;
 
    void Scale(const float scalar);
	//===================================================================================

	Vertex Scale() const { return _scale; };  // return the scale vector
	Vertex Rotation() const { return _rot; }; // return the rot vector
	Vertex Translation() const { return _pos; }; // return the pos vector

	void SetWorld(bool flag) { _isWorld = flag; };
	void CaptureKeys();
 
    unsigned int VertexCount() const;
    unsigned int IndexCount() const;
 
    void  GetWorldMatrix(Matrix4x4& mat);
    const Matrix4x4& GetWorldMatrix();

	GObject(const std::vector<Vertex> & vertices, const std::vector<unsigned short> & indices, const bool world);
	~GObject(void);
};

