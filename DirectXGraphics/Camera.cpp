#include "Camera.h"
#include "DirectInput.h"
#include "D3DApp.h"

Camera::Camera()
{
	_cameraType = AIRCRAFT;

	_pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_up    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

Camera::Camera(CameraType cameraType)
{
	_cameraType = cameraType;

	_pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_up    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

Camera::~Camera()
{

}

void Camera::SetLookAt(D3DXVECTOR3 &target)
{
	//D3DXVec3Normalize();
	D3DXVECTOR3 F = target - _pos;
	D3DXVec3Normalize(&F, &F);

	D3DXVECTOR3 R;// = 
	D3DXVec3Cross(&R, &_up, &F);// _up.Cross(F);
	D3DXVec3Normalize(&R, &R);
	//R.Normalize();

	D3DXVECTOR3 U;// = F.Cross(R);
	D3DXVec3Cross(&U, &F, &R);// _up.Cross(F);
	D3DXVec3Normalize(&U, &U);
	//U.Normalize();

	//m_Position		= pos;
	//m_Right			= R;
	//m_Up			= U;
	//m_Forward		= F;

	_right		= R;
	_up			= U;
	_look		= F;

	//BuildView();
	getViewMatrix();

	//m_ViewProj = m_View * m_Proj;
}

D3DXMATRIX Camera::getViewMatrix()
{
	D3DXMATRIX *V = &_view;
	// Keep camera's axes orthogonal to eachother
	D3DXVec3Normalize(&_look, &_look);

	D3DXVec3Cross(&_up, &_look, &_right);
	D3DXVec3Normalize(&_up, &_up);

	D3DXVec3Cross(&_right, &_up, &_look);
	D3DXVec3Normalize(&_right, &_right);

	// Build the view matrix:
	float x = -D3DXVec3Dot(&_right, &_pos);
	float y = -D3DXVec3Dot(&_up, &_pos);
	float z = -D3DXVec3Dot(&_look, &_pos);

	(*V)(0,0) = _right.x; (*V)(0, 1) = _up.x; (*V)(0, 2) = _look.x; (*V)(0, 3) = 0.0f;
	(*V)(1,0) = _right.y; (*V)(1, 1) = _up.y; (*V)(1, 2) = _look.y; (*V)(1, 3) = 0.0f;
	(*V)(2,0) = _right.z; (*V)(2, 1) = _up.z; (*V)(2, 2) = _look.z; (*V)(2, 3) = 0.0f;
	(*V)(3,0) = x;        (*V)(3, 1) = y;     (*V)(3, 2) = z;       (*V)(3, 3) = 1.0f;

	return _view;
}

void Camera::getPosition(D3DXVECTOR3* pos)
{
	*pos = _pos;
}

void Camera::setPosition(D3DXVECTOR3* pos)
{
	_pos = *pos;
}

void Camera::getRight(D3DXVECTOR3* right)
{
	*right = _right;
}

void Camera::getUp(D3DXVECTOR3* up)
{
	*up = _up;
}

void Camera::getLook(D3DXVECTOR3* look)
{
	*look = _look;
}

void Camera::walk(float units)
{
	// move only on xz plane for land object
	if( _cameraType == LANDOBJECT )
		_pos += D3DXVECTOR3(_look.x, 0.0f, _look.z) * units;

	if( _cameraType == AIRCRAFT )
		_pos += _look * units;
}

void Camera::strafe(float units)
{
	// move only on xz plane for land object
	if( _cameraType == LANDOBJECT )
		_pos += D3DXVECTOR3(_right.x, 0.0f, _right.z) * units;

	if( _cameraType == AIRCRAFT )
		_pos += _right * units;
}

void Camera::fly(float units)
{
	// move only on y-axis for land object
	if( _cameraType == LANDOBJECT )
		_pos.y += units;

	if( _cameraType == AIRCRAFT )
		_pos += _up * units;
}

void Camera::pitch(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &_right,	angle);

	// rotate _up and _look around _right vector
	D3DXVec3TransformCoord(&_up,&_up, &T);
	D3DXVec3TransformCoord(&_look,&_look, &T);
}

void Camera::yaw(float angle)
{
	D3DXMATRIX T;

	// rotate around world y (0, 1, 0) always for land object
	if( _cameraType == LANDOBJECT )
		D3DXMatrixRotationY(&T, angle);

	// rotate around own up vector for aircraft
	if( _cameraType == AIRCRAFT )
		D3DXMatrixRotationAxis(&T, &_up, angle);

	// rotate _right and _look around _up or y-axis
	D3DXVec3TransformCoord(&_right,&_right, &T);
	D3DXVec3TransformCoord(&_look,&_look, &T);
}

void Camera::roll(float angle)
{
	// only roll for aircraft type
	if( _cameraType == AIRCRAFT )
	{
		D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T, &_look,	angle);

		// rotate _up and _right around _look vector
		D3DXVec3TransformCoord(&_right,&_right, &T);
		D3DXVec3TransformCoord(&_up,&_up, &T);
	}
}

//void Camera::getViewMatrix(D3DXMATRIX* V)
//{
//	// Keep camera's axes orthogonal to eachother
//	D3DXVec3Normalize(&_look, &_look);
//
//	D3DXVec3Cross(&_up, &_look, &_right);
//	D3DXVec3Normalize(&_up, &_up);
//
//	D3DXVec3Cross(&_right, &_up, &_look);
//	D3DXVec3Normalize(&_right, &_right);
//
//	// Build the view matrix:
//	float x = -D3DXVec3Dot(&_right, &_pos);
//	float y = -D3DXVec3Dot(&_up, &_pos);
//	float z = -D3DXVec3Dot(&_look, &_pos);
//
//	(*V)(0,0) = _right.x; (*V)(0, 1) = _up.x; (*V)(0, 2) = _look.x; (*V)(0, 3) = 0.0f;
//	(*V)(1,0) = _right.y; (*V)(1, 1) = _up.y; (*V)(1, 2) = _look.y; (*V)(1, 3) = 0.0f;
//	(*V)(2,0) = _right.z; (*V)(2, 1) = _up.z; (*V)(2, 2) = _look.z; (*V)(2, 3) = 0.0f;
//	(*V)(3,0) = x;        (*V)(3, 1) = y;     (*V)(3, 2) = z;       (*V)(3, 3) = 1.0f;
//}

void Camera::setCameraType(CameraType cameraType)
{
	_cameraType = cameraType;
}


//Camera::Camera()
//{
//	yaw = 0.0f;
//	pitch = 0.0f;
//	roll = 0.0f;
//	position = D3DXVECTOR3(0.0f, 0.0f, 40.0f);
//}
//
//Camera::~Camera()
//{
//}
//
//void Camera::CalculateViewMatrix(D3DXMATRIX* viewMatrix)
//{
//	up=D3DXVECTOR3(0.0f,1.0f,0.0f);
//	look=D3DXVECTOR3(0.0f,0.0f,1.0f);
//	right=D3DXVECTOR3(1.0f,0.0f,0.0f);
//
//	D3DXMATRIX yawMatrix;
//	D3DXMatrixRotationAxis(&yawMatrix, &up, yaw);
//	D3DXVec3TransformCoord(&look, &look, &yawMatrix); 
//	D3DXVec3TransformCoord(&right, &right, &yawMatrix);
//
//	D3DXMATRIX pitchMatrix;
//	D3DXMatrixRotationAxis(&pitchMatrix, &right, pitch);
//	D3DXVec3TransformCoord(&look, &look, &pitchMatrix); 
//	D3DXVec3TransformCoord(&up, &up, &pitchMatrix);
//
//	D3DXMATRIX rollMatrix;
//	D3DXMatrixRotationAxis(&rollMatrix, &look, roll);
//	D3DXVec3TransformCoord(&right, &right, &rollMatrix);
//	D3DXVec3TransformCoord(&up, &up, &rollMatrix);
//	
//	//D3DXMATRIX viewMatrix;
//	D3DXMatrixIdentity(viewMatrix);
//
//	viewMatrix->_11 = right.x; viewMatrix->_12 = up.x; viewMatrix->_13 = look.x;
//	viewMatrix->_21 = right.y; viewMatrix->_22 = up.y; viewMatrix->_23 = look.y;
//	viewMatrix->_31 = right.z; viewMatrix->_32 = up.z; viewMatrix->_33 = look.z;
//
//	viewMatrix->_41 = - D3DXVec3Dot( &position, &right ); 
//	viewMatrix->_42 = - D3DXVec3Dot( &position, &up );
//	viewMatrix->_43 = - D3DXVec3Dot( &position, &look );
//
//	gD3DDev->SetTransform( D3DTS_VIEW, viewMatrix );
//
//	//projection matrix
//	D3DXMatrixPerspectiveFovLH(&m_projMatrix,
//                            D3DXToRadian(45),    // the horizontal field of view
//                            4 / 3,    // the aspect ratio
//                            1.0f,    // the near view-plane
//                            500.0f);    // the far view-plane
//}
//
//void Camera::Yaw(float amount)
//{
//   yaw+=amount;
//}
//
//void Camera::Pitch(float amount)
//{
//   pitch+=amount;
//}
//
//void Camera::Roll(float amount)
//{
//   roll+=amount;
//}
//
//void Camera::Forward(float d)
//{
//	position+=look*d;    // Move forward
//}
//
//void Camera::Backward(float d)
//{
//	position+=look*-d;    // Move backward
//}
//
//void Camera::Right(float d)
//{
//	position+=right*d;   // Move right (strafe)
//}
//
//void Camera::Left(float d)
//{
//	position+=right*-d;   // Move left
//}
//
//void Camera::Up(float d)
//{
//	position+=up*d;      // Move up
//}
//
//void Camera::Down(float d)
//{
//	position+=up*-d;      // Move down
//}
//
//void Camera::Update()
//{
//	if(gDInput->keyDown(DIK_W))
//	{
//		Forward(0.5f);
//	}
//	if(gDInput->keyDown(DIK_S))
//	{
//		Backward(0.5f);
//	}
//	if(gDInput->keyDown(DIK_A))
//	{
//		Left(0.5f);
//	}
//	if(gDInput->keyDown(DIK_D))
//	{
//		Right(0.5f);
//	}
//	if(gDInput->mouseButtonDown(0))
//	{
//		Yaw((gDInput->mouseDX()*0.01f));
//		Pitch((gDInput->mouseDY()*0.01f));
//	}
//
//	this->CalculateViewMatrix(&m_viewMatrix);
//}
//
//void Camera::SetPosition(D3DXVECTOR3 pos) 
//{
//	position = pos;
//	recalcVectors();
//}
//
//void Camera::SetTarget(D3DXVECTOR3 target) 
//{
//	look = target;
//	recalcVectors();
//}
//
//void Camera::recalcVectors()
//{
//	right	= D3DXVECTOR3(1.0f, 0.0f, 0.0f);	// the right axis from the camera's position
//	up	= D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//the up vector, default to Y
//
//	look = look - position;
//	D3DXVec3Normalize(&look, &look);
//
//	D3DXVec3Cross(&right, &up, &look);
//	D3DXVec3Cross(&up, &look, &right);
//}