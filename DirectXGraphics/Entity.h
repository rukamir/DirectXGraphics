#pragma once

#include <D3dx9math.h>
#include "BaseComponent.h"
//#include "MeshBase.h"

class Entity
{
protected:
	int				m_id;
	D3DXVECTOR3		m_velocity;
	D3DXVECTOR3		m_acceleration;
	D3DXVECTOR3		m_target;
	D3DXVECTOR3		m_forceAccum;
	int			m_targetID;
	int			m_awarenessDist;
	float		damping;

	double		m_awarnessRad;

	double		m_maxSpeed;
	double		m_maxAccel;
	D3DXVECTOR3		orientation;
public:
	D3DXVECTOR3		m_pos;
	GraphicsComponent				*m_Graphics;

	Entity(){}
	Entity(int id)					{SetID(id);}
	~Entity(){}
	void Update(float t)
	{
		m_pos = m_pos + m_velocity * t;
		m_velocity = m_velocity * pow(damping, t) + m_acceleration * t;

		D3DXVECTOR3 resultAccel = m_acceleration;

		resultAccel += m_forceAccum;// * m_inverseMass;
		m_velocity += resultAccel * t;
		m_velocity = m_velocity * pow(damping, t);
	
		//update physics and graphics here
		//m_mesh->SetPos( this->m_pos );
	
		//clear stuff
		m_forceAccum = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//m_neighbors.clear();
		m_acceleration= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//if(m_mesh)
		//	m_mesh->SetPos(this->m_pos);
	}
	void UpdateHeading()
	{
		////heading update
		D3DXVECTOR3 orient = orientation;// = vector3(0,0,1);

		//find rotation angel
		D3DXVECTOR3 a = D3DXVECTOR3( 1.0f,0.0f,0.0f);
		D3DXVECTOR3 b = this->GetVelo();
		D3DXVec3Normalize(&b, &b);

		//float theta = acos( a * b ); // dot product
		float theta = D3DXVec3Dot(&a, &b);

		//the previous step will always return a positive number
		if ( a.y * b.x > a.x * b.y )
			theta *= -1;

		double w = cos(theta/2);
		 orient.x = orientation.x * sin(theta/2);
		 orient.y = orientation.y * sin(theta/2); 
		 orient.z = orientation.z * sin(theta/2); 

		 //gMyGameWorld->SetTriangleHeading(this->GetID(),D3DXQUATERNION(orient.x,orient.y,orient.z,w));
		 //m_gObject->SetHeading(D3DXQUATERNION(orient.x,orient.y,orient.z,w));
		 //m_mesh->SetRotateX(orient.x);
		 //m_mesh->SetRotateY(orient.y);
		 //m_mesh->SetRotateZ(orient.z);
	}

	void AddForce(D3DXVECTOR3 force)			
	{
		m_forceAccum += force;
	}

	//set functions
	void		SetID(int id)				{m_id = id;}
	void		SetPosition(D3DXVECTOR3 pos)	{m_pos = pos;}
	void		SetVelocity(D3DXVECTOR3 velo)	{m_velocity = velo;}
	void		SetTargetID(int id)			{m_targetID = id;}
	void		SetTarget(D3DXVECTOR3 pos)		{m_target = pos;}
	void		SetDamping(float damp)		{damping = damp;}
	void		SetAcceleration(D3DXVECTOR3 a)	{m_acceleration = a;}
	void		SetMaxSpeed(double speed)	{m_maxSpeed = speed;}
	void		SetMaxAccel(double accel)	{m_maxAccel = accel;}
	void		SetOrientation(D3DXVECTOR3 orient) {orientation = orient;}
	//void		SetCurrentState(current_state set){m_state = set;}
	void		SetAwarnessRadius(double rad)	{m_awarnessRad = rad;}
	//void RotateX(float rotX)				{m_mesh->SetRotateX(rotX);}
	//void RotateY(float rotY)				{m_mesh->SetRotateY(rotY);}
	//void RotateZ(float rotZ)				{m_mesh->SetRotateZ(rotZ);}


	//get functions
	double		GetAwarnessRadius()			{return m_awarnessRad;}
	int			GetID()						{return m_id;}
	D3DXVECTOR3		GetPosition()				{return m_pos;}
	D3DXVECTOR3		GetTarget()					{return m_target;}
	D3DXVECTOR3		GetVelo()					{return m_velocity;}
	D3DXVECTOR3		GetAcceleration()			{return m_acceleration;}
	float		GetDamp()					{return damping;}
	double		GetMaxSpeed()				{return m_maxSpeed;}
	double		GetMaxAccel()				{return m_maxAccel;}
	//current_state GetCurrentState()			{return m_state;}
};	// end Entity class