#include "GObject.h"

DWORD KEY_W = 0x57;
DWORD KEY_S = 0x53;
DWORD KEY_A = 0x41;
DWORD KEY_D = 0x44;
DWORD KEY_G = 0x47;
DWORD KEY_H = 0x48;
DWORD KEY_I = 0x49;
DWORD KEY_V = 0x56;
DWORD KEY_B = 0x42;
DWORD Key_O = 0x4F;
DWORD Key_L = 0x4C;
DWORD Key_M = 0x4D;
DWORD Key_N = 0x4E;
DWORD Key_F = 0x46;
DWORD Key_0 = 0x30;
DWORD Key_9 = 0x39;

GObject::GObject(const std::vector<Vertex> & vertices, const std::vector<unsigned short> & indices, const bool world)
{
	InitializeVert(vertices);
	InitializeIndices(indices);

	worldMatrix.Identity();

	isDirty = false;
	displayBasis = true;
	isWorld = world;
	filled = false;

	arbRot = 0;
	rot = Vertex();
	pos = Vertex();
	trans = Vertex();
	scale = Vertex(1.0f, 1.0f, 1.0f);
	arbAxis = Vertex(1.0f, 0.0f, 0.0f);
}


GObject::~GObject(void)
{
}

void GObject::SetPos(const Vertex & offset)
{
		pos.x = offset.x;
		pos.y = offset.y;
		pos.z = offset.z;

		worldMatrix.SetPos(pos);
}

void GObject::Scale(const float scalar)
{
	if ( scale != scalar)
	{
		scale.x = scalar;
		scale.y = scalar;
		scale.z = scalar;

		isDirty = true;
	}
}

void GObject::TranslateX(const float & translate)
{
	trans.x += translate;

	isDirty = true;
}

void GObject::TranslateY(const float & translate)
{
	trans.y += translate;

	isDirty = true;
}

void GObject::TranslateZ(const float & translate)
{
	trans.z += translate;

	isDirty = true;
}

void GObject::Translate(const Vertex & translate) 
{
		trans.x += translate.x;
		trans.y += translate.y;
		trans.z += translate.z;

		isDirty = true;
}

void GObject::InitializeVert(const std::vector<Vertex> & vertices)
{
	verts = vertices;
}

void GObject::InitializeIndices(const std::vector<unsigned short> & indices)
{
	index = indices;
}

std::vector<Vertex> * GObject::AccessVertices()
{
	std::vector<Vertex> * pVertices = &verts;
	return pVertices;
}

std::vector<unsigned short> * GObject::AccessIndices()
{
	std::vector<unsigned short> * pIndices = &index;
	return pIndices;
}

unsigned int GObject::VertexCount() const
{
	unsigned int count = 0;

	for ( unsigned int i = 0; i < verts.size(); i++)
	{
		count++;
	}

	return count;
}

unsigned int GObject::IndexCount() const
{
	unsigned int count = 0;

	for (unsigned int i = 0; i < verts.size(); i++)
	{
		count++;
	}

	return count;
}

void GObject::GetWorldMatrix(Matrix4x4& mat)
{
	if (isDirty == true)
	{
		if (isWorld == false)
		{
			mat.Identity();
			mat.Scale(scale);
			mat.EulerRotation(rot);
			mat.ArbAxisRotation(arbAxis, arbRot);
			mat.SetPos(pos);
			mat.Translation(trans);
		}
		else
		{
			mat.Identity();
			mat.Scale(scale);
			mat.SetPos(pos);
			mat.Translation(trans);
			mat.EulerRotation(rot);
		}
		worldMatrix = mat;

		isDirty = false;
	}
	else
	{
		mat = worldMatrix;
	}
}

const Matrix4x4& GObject::GetWorldMatrix()
{
	return worldMatrix;
}

void GObject::Render(Rasterizer& raster)
{
	Matrix4x4 tempMatrix;
	GetWorldMatrix(tempMatrix);
	raster.ProcessVertices(verts, index, tempMatrix, filled); 
}

void GObject::RotateX(float degrees) 
{
		isDirty = true; 
		rot.x += degrees;
} 

void GObject::RotateY(float degrees) 
{ 
		isDirty = true; 
		rot.y += degrees;
} 

void GObject::RotateZ(float degrees) 
{ 
		isDirty = true; 
		rot.z += degrees;
} 

void GObject::Fill(bool fill)
{
	filled = fill;
}

void GObject::SetArbAxis(Vertex & verts)
{
	arbAxis = verts;
	arbAxis.Normalize();
}

void GObject::CaptureKeys()
{
	float tempXRot;
	float tempYRot;
	float tempZRot;
	float tempTrans;

	if (GetAsyncKeyState(Key_O) != 0)
	{
		tempXRot = 2.0f;
		RotateX(tempXRot);
	}

	if (GetAsyncKeyState(Key_L) != 0)
	{
		tempXRot = -2.0f;
		RotateX(tempXRot);
	}
	
	/*if (GetAsyncKeyState(KEY_H) != 0)
	{
		isDirty = true;
		arbRot += 2.0f;
	}

	if (GetAsyncKeyState(KEY_I) != 0)
	{
		isDirty = true;
		arbRot -= 2.0f;
	}*/

	if (GetAsyncKeyState(KEY_V) != 0)
	{
		tempZRot = 2.0f;
		RotateZ(tempZRot);
	}

	if (GetAsyncKeyState(KEY_B) != 0)
	{
		tempZRot = -2.0f;
		RotateZ(tempZRot);
	}

	if (GetAsyncKeyState(KEY_H) != 0)
	{
		tempYRot = 2.0f;
		RotateY(tempYRot);
	}

	if (GetAsyncKeyState(KEY_I) != 0)
	{
		tempYRot = -2.0f;
		RotateY(tempYRot);
	}

	if (GetAsyncKeyState(Key_M) != 0)
	{
		tempTrans = .04f;
		TranslateX(tempTrans);
	}

	if (GetAsyncKeyState(Key_N) != 0)
	{
		tempTrans = -.04f;
		TranslateX(tempTrans);
	}

	if (GetAsyncKeyState(Key_9) != 0)
	{
		scale.x += 0.07;
		scale.y += 0.07;
		scale.z += 0.07;
		Scale(scale.x);
	}

	if (GetAsyncKeyState(Key_0) != 0)
	{
		scale.x -= 0.07;
		scale.y -= 0.07;
		scale.z -= 0.07;
		Scale(scale.x);
		if (scale.x < 0.01 || scale.y < 0.01 || scale.z < 0.01)
		{
			scale.x = 0.01;
			scale.y = 0.01;
			scale.z = 0.01;
		}
	}

	if (GetKeyState(Key_F) == 0)
	{
		filled = true;
	}

	if (GetKeyState(Key_F) != 0)
	{
		filled = false;
	}

}