#pragma once
#include "Matrix4x4.h"
#include "Vertex.h"
#include "Keys.h"
#include <iostream>
using namespace std;

class Camera
{
	static unsigned short numCameras;

	//Matrix builders
	Matrix4x4 _cameraMat;
	Vertex _rightView;
	Vertex _upView;
	Vertex _forwardView;

	//Camera positioning
	Vertex _leftFac;
	Vertex _upFac;
	Vertex _forwardFac;
	float _cameraSpeed;

	Vertex _pos;
	Vertex _rot;
	
	HWND _hWnd;
	RECT _wBounds;
	RECT _oldClip;
	RECT _newClip;
	POINT _mousePos;
	POINT _wCenter;

	bool _speedTrig;
	bool _haveHandle;
	bool _isDirty;
	bool _isActive;
	bool _noClip;
public:

	Camera();
	Camera(Vertex& leftView, Vertex& upView, Vertex& forwardView, bool noClip);
	Camera(Vertex& leftView, Vertex& upView, Vertex& forwardView, Vertex& pos, bool noClip);

	void GetWindow(const HWND & hWnd) {  _hWnd = hWnd; _haveHandle = true; SetWindow(); }
	void SetWindow() { 	GetWindowRect(_hWnd, &_newClip); ClipCursor(&_newClip); }
	void CalcWinCenter();
	void SetCameraSpeed(float speed) { _cameraSpeed = speed; };
	void SetCameraUp(Vertex& upView) { _upView = upView; };
	void SetCameraLeft(Vertex& rightView) { _rightView = rightView; };
	void SetCameraForward(Vertex& forwardView) { _forwardView = forwardView; };
	float ToRadians(float degrees);

	static unsigned short GetNumCameras() { return numCameras; };

	Vertex GetPosition() { return _pos;};
	Vertex GetRotation() { return _rot;};
	Vertex GetLeftView() { return _rightView; };
	Vertex GetUpView() { return _upView; };
	Vertex GetForwardView() { return _forwardView; };

	void RotFac();

	
	//Flags Dirty
	//===========================
	void RotX(float x);
	void RotY(float y);
	void RotZ(float z);
	void TransX(float x);
	void TransY(float y);
	void TransZ(float z);
	void Rotate(Vertex& rot);
	void Translate(Vertex& trans);
	void SetPos(Vertex& offset);
	//============================

	bool GetActivety() { return _isActive; };
	void BuildMatrix(Matrix4x4 & camMatrix);
	void GetCameraMatrix(Matrix4x4& camMatrix, Vertex& vert);
	void Listen() { ListenKeys(); ListenMouse();};
	void ListenKeys();
	void ListenMouse();
	void CalcMouseRot(POINT & ptr);
	Matrix4x4 GetCameraMatrix();

	~Camera(void){};
};