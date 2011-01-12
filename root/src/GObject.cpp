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

	_worldMatrix.Identity();

	_isDirty = false;
	_displayBasis = true;
	_isWorld = world;
	_filled = false;

	_arbRot = 0;
	_rot = Vertex();
	_pos = Vertex();
	_trans = Vertex();
	_scale = Vertex(1.0f, 1.0f, 1.0f);
	_arbAxis = Vertex(1.0f, 0.0f, 0.0f);
}


GObject::~GObject(void)
{
}

void GObject::SetPos(const Vertex & offset)
{
		_pos._x = offset._x;
		_pos._y = offset._y;
		_pos._z = offset._z;

		_worldMatrix.SetPos(_pos);
}

void GObject::Scale(const float scalar)
{
	if ( _scale != scalar)
	{
		_scale._x = scalar;
		_scale._y = scalar;
		_scale._z = scalar;

		_isDirty = true;
	}
}

void GObject::TranslateX(const float & translate)
{
	_trans._x += translate;

	_isDirty = true;
}

void GObject::TranslateY(const float & translate)
{
	_trans._y += translate;

	_isDirty = true;
}

void GObject::TranslateZ(const float & translate)
{
	_trans._z += translate;

	_isDirty = true;
}

void GObject::Translate(const Vertex & translate) 
{
		_trans._x += translate._x;
		_trans._y += translate._y;
		_trans._z += translate._z;

		_isDirty = true;
}

void GObject::InitializeVert(const std::vector<Vertex> & vertices)
{
	_verts = vertices;
}

void GObject::InitializeIndices(const std::vector<unsigned short> & indices)
{
	_index = indices;
}

std::vector<Vertex> * GObject::AccessVertices()
{
	std::vector<Vertex> * pVertices = &_verts;
	return pVertices;
}

std::vector<unsigned short> * GObject::AccessIndices()
{
	std::vector<unsigned short> * pIndices = &_index;
	return pIndices;
}

unsigned int GObject::VertexCount() const
{
	unsigned int count = 0;

	for ( unsigned int i = 0; i < _verts.size(); i++)
	{
		count++;
	}

	return count;
}

unsigned int GObject::IndexCount() const
{
	unsigned int count = 0;

	for (unsigned int i = 0; i < _verts.size(); i++)
	{
		count++;
	}

	return count;
}

void GObject::GetWorldMatrix(Matrix4x4& mat)
{
	if (_isDirty == true)
	{
		if (_isWorld == false)
		{
			mat.Identity();
			mat.Scale(_scale);
			mat.EulerRotation(_rot);
			mat.ArbAxisRotation(_arbAxis, _arbRot);
			mat.SetPos(_pos);
			mat.Translation(_trans);
		}
		else
		{
			mat.Identity();
			mat.Scale(_scale);
			mat.SetPos(_pos);
			mat.Translation(_trans);
			mat.EulerRotation(_rot);
		}
		_worldMatrix = mat;

		_isDirty = false;
	}
	else
	{
		mat = _worldMatrix;
	}
}

const Matrix4x4& GObject::GetWorldMatrix()
{
	return _worldMatrix;
}

void GObject::Render(Rasterizer& raster)
{
	Matrix4x4 tempMatrix;
	GetWorldMatrix(tempMatrix);
	raster.ProcessVertices(_verts, _index, tempMatrix, _filled); 
}

void GObject::RotateX(float degrees) 
{
		_isDirty = true; 
		_rot._x += degrees;
} 

void GObject::RotateY(float degrees) 
{ 
		_isDirty = true; 
		_rot._y += degrees;
} 

void GObject::RotateZ(float degrees) 
{ 
		_isDirty = true; 
		_rot._z += degrees;
} 

void GObject::Fill(bool fill)
{
	_filled = fill;
}

void GObject::SetArbAxis(Vertex & verts)
{
	_arbAxis = verts;
	_arbAxis.Normalize();
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
		_scale._x += 0.07;
		_scale._y += 0.07;
		_scale._z += 0.07;
		Scale(_scale._x);
	}

	if (GetAsyncKeyState(Key_0) != 0)
	{
		_scale._x -= 0.07;
		_scale._y -= 0.07;
		_scale._z -= 0.07;
		Scale(_scale._x);
		if (_scale._x < 0.01 || _scale._y < 0.01 || _scale._z < 0.01)
		{
			_scale._x = 0.01;
			_scale._y = 0.01;
			_scale._z = 0.01;
		}
	}

	if (GetKeyState(Key_F) == 0)
	{
		_filled = true;
	}

	if (GetKeyState(Key_F) != 0)
	{
		_filled = false;
	}

}