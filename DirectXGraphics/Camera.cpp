#include "Camera.h"
#include "DirectInput.h"
#include "D3DApp.h"

Camera::Camera()
{
	yaw = 0.0f;
	pitch = 0.0f;
	roll = 0.0f;
	position = D3DXVECTOR3(0.0f, 0.0f, 40.0f);
}

Camera::~Camera()
{
}

void Camera::CalculateViewMatrix(D3DXMATRIX* viewMatrix)
{
	up=D3DXVECTOR3(0.0f,1.0f,0.0f);
	look=D3DXVECTOR3(0.0f,0.0f,1.0f);
	right=D3DXVECTOR3(1.0f,0.0f,0.0f);

	D3DXMATRIX yawMatrix;
	D3DXMatrixRotationAxis(&yawMatrix, &up, yaw);
	D3DXVec3TransformCoord(&look, &look, &yawMatrix); 
	D3DXVec3TransformCoord(&right, &right, &yawMatrix);

	D3DXMATRIX pitchMatrix;
	D3DXMatrixRotationAxis(&pitchMatrix, &right, pitch);
	D3DXVec3TransformCoord(&look, &look, &pitchMatrix); 
	D3DXVec3TransformCoord(&up, &up, &pitchMatrix);

	D3DXMATRIX rollMatrix;
	D3DXMatrixRotationAxis(&rollMatrix, &look, roll);
	D3DXVec3TransformCoord(&right, &right, &rollMatrix);
	D3DXVec3TransformCoord(&up, &up, &rollMatrix);
	
	//D3DXMATRIX viewMatrix;
	D3DXMatrixIdentity(viewMatrix);

	viewMatrix->_11 = right.x; viewMatrix->_12 = up.x; viewMatrix->_13 = look.x;
	viewMatrix->_21 = right.y; viewMatrix->_22 = up.y; viewMatrix->_23 = look.y;
	viewMatrix->_31 = right.z; viewMatrix->_32 = up.z; viewMatrix->_33 = look.z;

	viewMatrix->_41 = - D3DXVec3Dot( &position, &right ); 
	viewMatrix->_42 = - D3DXVec3Dot( &position, &up );
	viewMatrix->_43 = - D3DXVec3Dot( &position, &look );

	gD3DDev->SetTransform( D3DTS_VIEW, viewMatrix );

	//projection matrix
	D3DXMatrixPerspectiveFovLH(&m_projMatrix,
                            D3DXToRadian(45),    // the horizontal field of view
                            4 / 3,    // the aspect ratio
                            1.0f,    // the near view-plane
                            500.0f);    // the far view-plane
}

void Camera::Yaw(float amount)
{
   yaw+=amount;
}

void Camera::Pitch(float amount)
{
   pitch+=amount;
}

void Camera::Roll(float amount)
{
   roll+=amount;
}

void Camera::Forward(float d)
{
	position+=look*d;    // Move forward
}

void Camera::Backward(float d)
{
	position+=look*-d;    // Move backward
}

void Camera::Right(float d)
{
	position+=right*d;   // Move right (strafe)
}

void Camera::Left(float d)
{
	position+=right*-d;   // Move left
}

void Camera::Up(float d)
{
	position+=up*d;      // Move up
}

void Camera::Down(float d)
{
	position+=up*-d;      // Move down
}

void Camera::Update()
{
	if(gDInput->keyDown(DIK_W))
	{
		Forward(0.5f);
	}
	if(gDInput->keyDown(DIK_S))
	{
		Backward(0.5f);
	}
	if(gDInput->keyDown(DIK_A))
	{
		Left(0.5f);
	}
	if(gDInput->keyDown(DIK_D))
	{
		Right(0.5f);
	}
	if(gDInput->mouseButtonDown(0))
	{
		Yaw((gDInput->mouseDX()*0.01f));
		Pitch((gDInput->mouseDY()*0.01f));
	}

	this->CalculateViewMatrix(&m_viewMatrix);
}

void Camera::SetPosition(D3DXVECTOR3 pos) 
{
	position = pos;
	recalcVectors();
}

void Camera::SetTarget(D3DXVECTOR3 target) 
{
	look = target;
	recalcVectors();
}

void Camera::recalcVectors()
{
	right	= D3DXVECTOR3(1.0f, 0.0f, 0.0f);	// the right axis from the camera's position
	up	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//the up vector, default to Y

	look = look - position;
	D3DXVec3Normalize(&look, &look);

	D3DXVec3Cross(&right, &up, &look);
	D3DXVec3Cross(&up, &look, &right);
}