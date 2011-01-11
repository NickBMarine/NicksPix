#pragma once
#include "Rasterizer.h"
#include "NPolygon.h"
#include "Keys.h"

class GObject
{
	std::vector<NPolygon> _polygon;
	std::vector<Vertex> verts;
	std::vector<unsigned short> index;

	Matrix4x4 worldMatrix;

	bool isDirty;
	bool isWorld;
	bool displayBasis;
	bool filled;

	Vertex rot;
	Vertex trans;
	Vertex pos;
	Vertex scale;
	Vertex arbAxis;

	float arbRot;

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
 
	void ScaleX(float scalar) { if (scalar != scale.x) { isDirty = true; scale.x = scalar; } } ;
	void ScaleY(float scalar) { if (scalar != scale.y) { isDirty = true; scale.y = scalar; } } ;
	void ScaleZ(float scalar) { if (scalar != scale.z) { isDirty = true; scale.z = scalar; } } ;
 
    void Scale(const float scalar);
	//===================================================================================

	Vertex Scale() const { return scale; };  // return the scale vector
	Vertex Rotation() const { return rot; }; // return the rot vector
	Vertex Translation() const { return pos; }; // return the pos vector

	void SetWorld(bool flag) { isWorld = flag; };
	void CaptureKeys();
 
    unsigned int VertexCount() const;
    unsigned int IndexCount() const;
 
    void  GetWorldMatrix(Matrix4x4& mat);
    const Matrix4x4& GetWorldMatrix();

	GObject(const std::vector<Vertex> & vertices, const std::vector<unsigned short> & indices, const bool world);
	~GObject(void);
};

