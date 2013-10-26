#pragma once

#include <d3dx9.h>

class Camera
{
public:
	enum CameraType { LANDOBJECT, AIRCRAFT };

	Camera();
	Camera(CameraType cameraType);
	~Camera();

	void SetLookAt(D3DXVECTOR3 &target);
	D3DXMATRIX getViewMatrix();

	void strafe(float units); // left/right
	void fly(float units);    // up/down
	void walk(float units);   // forward/backward
	
	void pitch(float angle); // rotate on right vector
	void yaw(float angle);   // rotate on up vector
	void roll(float angle);  // rotate on look vector

	//void getViewMatrix(D3DXMATRIX* V); 
	void setCameraType(CameraType cameraType); 
	void getPosition(D3DXVECTOR3* pos); 
	void setPosition(D3DXVECTOR3* pos); 

	void getRight(D3DXVECTOR3* right);
	void getUp(D3DXVECTOR3* up);
	void getLook(D3DXVECTOR3* look);
private:
	CameraType  _cameraType;
	D3DXVECTOR3 _right;
	D3DXVECTOR3 _up;
	D3DXVECTOR3 _look;
	D3DXVECTOR3 _pos;
	D3DXMATRIX	_view;
};


//#ifndef CAMERA_H
//#define CAMERA_H
//
//#include <d3dx9.h>
//
////#define CAM Camera::Instance()
//
//class Camera
//{
//private:
//	D3DXMATRIX				m_viewMatrix;
//	D3DXMATRIX				m_projMatrix;
//	D3DXVECTOR3 position;      // camera position
//	float yaw;                 // rotation around the y axis
//	float pitch;               // rotation around the x axis
//	float roll;                // rotation around the z axis
//	D3DXVECTOR3 up,look,right; // camera axis
//	void recalcVectors();
//public:
//	Camera();
//	~Camera();
//
//	void CalculateViewMatrix(D3DXMATRIX* viewMatrix);
//	void SetPosition(D3DXVECTOR3 pos);
//	void SetTarget(D3DXVECTOR3 target);
//
//	void Yaw(float amount);
//	void Pitch(float amount);
//	void Roll(float amount);
//	void Forward(float d);
//	void Backward(float d);
//	void Right(float d);
//	void Left(float d);
//	void Up(float d);
//	void Down(float d);
//	void Update();
//
//	D3DXMATRIX GetViewMatrix()
//		{return m_viewMatrix;}
//	D3DXMATRIX GetProjectionMatrix()
//		{ return m_projMatrix;}
//	D3DXVECTOR3 GetCamPos()
//		{return this->position;}
//
//
//	static Camera* Instance()
//	{	static Camera instance; return &instance; }
//};
//
//#endif