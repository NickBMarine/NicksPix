#include "Camera.h"

Camera::Camera()
{
	numCameras++;
	_cameraSpeed = 0.1f;
	_isDirty = true;
	_noClip = true;
	_haveHandle = false;
	_speedTrig = false;
	_rightView = Vertex(1.0f, 0.0f, 0.0f);
	_upView = Vertex(0.0f, 1.0f, 0.0f);
	_forwardView = Vertex(0.0f, 0.0f, 1.0f);
	_pos = Vertex();
	_rot = Vertex();
	_leftFac = _rightView;
	_forwardFac = _forwardView;
	_upFac = Vertex();
	GetClipCursor(&_oldClip); 
	ShowCursor(false);
	CalcWinCenter();
}

Camera::Camera(Vertex& leftView, Vertex& upView, Vertex& forwardView, bool noClip = false)
{
	numCameras++;
	_noClip = noClip;
	_isDirty = false;
	_haveHandle = false;
	_speedTrig = false;
	_rightView = leftView;
	_upView = upView;
	_forwardView = forwardView;
	_pos = Vertex();
	_rot = Vertex();
	GetClipCursor(&_oldClip); 
	ShowCursor(false);
	CalcWinCenter();
}

Camera::Camera(Vertex& leftView, Vertex& upView, Vertex& forwardView, Vertex& pos, bool noClip = false)
{
	numCameras++;
	_noClip = noClip;
	_isDirty = false;
	_haveHandle = false;
	_speedTrig = false;
	_rightView = leftView;
	_upView = upView;
	_forwardView = forwardView;
	_pos = pos;
	_rot = Vertex();
	GetClipCursor(&_oldClip); 
	ShowCursor(false);
	CalcWinCenter();
}

float Camera::ToRadians(float degrees)
{
	float radians = degrees * (float(PI)/180.0f);
	return radians;
}

void Camera::RotX(float x)
{
	_rot._x += x;
	_isDirty = true;
}

void Camera::RotY(float y)
{
	_rot._y += y;
	_isDirty = true;
}

void Camera::RotZ(float z)
{
	_rot._z += z;
	_isDirty = true;
}

void Camera::RotFac()
{

	_forwardFac._x = sin(ToRadians(_rot._y));
	_forwardFac._z = cos(ToRadians(_rot._y));
	_leftFac._x = cos(ToRadians(_rot._y));
	_leftFac._z = -sin(ToRadians(_rot._y));

	if ( _noClip)
	{
		_upFac._y = -sin(ToRadians(_rot._x));
	}
}

void Camera::TransX(float x)
{
	_pos._x = x;
	_isDirty = true;

}

void Camera::TransY(float y)
{
	_pos._y = y;
	_isDirty = true;
}

void Camera::TransZ(float z)
{
	_pos._z = z;
	_isDirty = true;
}

void Camera::Rotate(Vertex& rot)
{
	_rot += rot;
	_isDirty = true;
}


void Camera::Translate(Vertex& trans)
{

	_pos += trans;
	_isDirty = true;
}

void Camera::SetPos(Vertex& offSet)
{
	_pos = offSet;
	_isDirty = true;
}

Matrix4x4 Camera::GetCameraMatrix()
{
	return _cameraMat; 
}

void Camera::GetCameraMatrix(Matrix4x4& camMatrix, Vertex& vert)
{
	if (_isDirty == true)
	{
		BuildMatrix(camMatrix);
		Vertex tempVec = _pos;
		tempVec.Negate();
		camMatrix.Transpose();
		camMatrix.Transformation(tempVec);
		camMatrix.SetPos(tempVec);
		_cameraMat = camMatrix;
		vert = _pos;

		_isDirty = false;
	}
	else
	{
		camMatrix = _cameraMat;
		vert = _pos;
	}
}

void Camera::BuildMatrix(Matrix4x4 & camMatrix)
{
	camMatrix.Identity();
	camMatrix.EulerRotation(_rot);

	Vertex temp(0.0f, 0.0f, 1.0f);
	Vertex upWorld(0.0f, 1.0f, 0.0f);
	Vertex forwardWorld(0.0f, 0.0f, 1.0f);

	camMatrix.Transformation(temp);

	if (upWorld.GetDotProduct(temp) != 1 && upWorld.GetDotProduct(temp) != -1)
		_rightView = upWorld.GetNormal(temp);
	else
		_rightView = forwardWorld.GetNormal(temp);

	_upView = temp.GetNormal(_rightView);

	camMatrix.SetRowOne(_rightView);
	camMatrix.SetRowTwo(_upView);
	camMatrix.SetRowThree(temp);

	_forwardView = temp;
}

void Camera::ListenKeys()
{
	float fac = 0.1;

	if (GetAsyncKeyState(VK_LSHIFT) != 0)
	{
		_speedTrig = true;
		_cameraSpeed *= 2.0f;
	}

	if (GetAsyncKeyState(VK_LCONTROL) != 0)
	{
		if (GetAsyncKeyState(KEY_W) != 0)
		{
			_pos += _upView * _cameraSpeed;
			_isDirty = true;
		}

		if (GetAsyncKeyState(KEY_S) != 0)
		{
			_pos -= _upView * _cameraSpeed;
			_isDirty = true;
		}
	}
	else
	{
		if (GetAsyncKeyState(KEY_W) != 0)
		{
			_pos += _forwardView * _cameraSpeed;
			_isDirty = true;
		}

		if (GetAsyncKeyState(KEY_S) != 0)
		{
			_pos -= _forwardView * _cameraSpeed;
			_isDirty = true;
		}
	}

	if (GetAsyncKeyState(KEY_A) != 0)
	{
		_pos -= _rightView * _cameraSpeed;
		_isDirty = true;
	}

	if (GetAsyncKeyState(KEY_D) != 0)
	{
		_pos += _rightView * _cameraSpeed;
		_isDirty = true;
	}

	if ( _speedTrig)
	{
		_cameraSpeed *= 0.5f;
		_speedTrig = false;
	}

	if (GetAsyncKeyState(VK_RIGHT)!=0)
	{
		RotY(1.0f);
		_isDirty = true;
	}

	if (GetAsyncKeyState(VK_LEFT)!=0)
	{
		RotY(-1.0f);
		_isDirty = true;
	}

	if (GetAsyncKeyState(VK_UP)!=0)
	{
		RotX(-1.0f);
		_isDirty = true;
	}

	if (GetAsyncKeyState(VK_DOWN)!=0)
	{
		RotX(1.0f);
		_isDirty = true;
	}
}

void Camera::ListenMouse()
{
	POINT ptr;

	GetCursorPos(&ptr);

	if (GetAsyncKeyState(VK_ESCAPE) != 0)
	{
		ClipCursor(&_oldClip);
	}

	CalcMouseRot(ptr);
	_mousePos = ptr;

	if ( _mousePos.x == _newClip.left || _mousePos.x == (_newClip.right-1) 
		|| _mousePos.y == _newClip.top || _mousePos.y == (_newClip.bottom-1))
	{
		_mousePos.x = _wCenter.x;
		_mousePos.y = _wCenter.y;
		SetCursorPos(_wCenter.x, _wCenter.y);
	}
}

void Camera::CalcMouseRot(POINT & ptr)
{
	Vertex tempAng;
	if ( !_haveHandle)
	{
		return;
	}
	if ( ptr.x > _mousePos.x)
	{
		tempAng._y = .03 * (ptr.x - _mousePos.x);
	}

	if ( ptr.x < _mousePos.x)
	{
		tempAng._y = -.03 * (_mousePos.x - ptr.x);
	}

	if ( ptr.y > _mousePos.y)
	{
		tempAng._x = .03 * (ptr.y  - _mousePos.y);
	}

	if ( ptr.y < _mousePos.y)
	{
		tempAng._x = -.03 * (_mousePos.y - ptr.y);
	}

	Rotate(tempAng);
}

void Camera::CalcWinCenter()
{
	_wCenter.y = (_oldClip.bottom - _oldClip.top)/2;
	_wCenter.x = (_oldClip.right - _oldClip.left)/2;
}