#ifndef CAMERA_H
#define CAMERA_H

#include <d3dx9.h>

#define CAM Camera::Instance()

class Camera
{
private:
	D3DXMATRIX				m_viewMatrix;
	D3DXMATRIX				m_projMatrix;
	D3DXVECTOR3 position;      // camera position
	float yaw;                 // rotation around the y axis
	float pitch;               // rotation around the x axis
	float roll;                // rotation around the z axis
	D3DXVECTOR3 up,look,right; // camera axis
	void recalcVectors();
public:
	Camera();
	~Camera();

	void CalculateViewMatrix(D3DXMATRIX* viewMatrix);
	void SetPosition(D3DXVECTOR3 pos);
	void SetTarget(D3DXVECTOR3 target);

	void Yaw(float amount);
	void Pitch(float amount);
	void Roll(float amount);
	void Forward(float d);
	void Backward(float d);
	void Right(float d);
	void Left(float d);
	void Up(float d);
	void Down(float d);
	void Update();

	D3DXMATRIX GetViewMatrix()
		{return m_viewMatrix;}
	D3DXMATRIX GetProjectionMatrix()
		{ return m_projMatrix;}
	D3DXVECTOR3 GetCamPos()
		{return this->position;}


	static Camera* Instance()
	{	static Camera instance; return &instance; }
};

#endif