#pragma once

#include "State.h"
#include <assert.h>

template <class entity_type>
class FSM
{
public:
	//State Machine Owener
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState;
	State<entity_type>* m_pPreviousState;

	//call this to update the FSM
	void Update(float dt)const
	{	
		m_pCurrentState->UpdateScene(m_pOwner, dt);
	}

	void Render()
	{	m_pCurrentState->RenderScene(m_pOwner);}

	FSM(){}
	FSM(entity_type* owner)
	{	
		m_pOwner = owner;
		m_pCurrentState = 0;
		m_pPreviousState = 0;
	}
	~FSM()
	{ 
		m_pCurrentState->LeaveState(m_pOwner);
		m_pOwner = 0; delete m_pOwner; delete m_pCurrentState; 
		if(m_pPreviousState)
			delete m_pPreviousState;}

	//change to a new state
	void ChangeState(State<entity_type>* pNewState)
	{
		assert(pNewState &&
		"<StateMachine::ChangeState>: trying to change to a null state");
		//keep a record of the previous state
		m_pPreviousState = m_pCurrentState;
		//call the exit method of the existing state
		m_pCurrentState->LeaveState(m_pOwner);
		//change state to the new state
		m_pCurrentState = pNewState;
		//call the entry method of the new state
		m_pCurrentState->InitializeState(m_pOwner);
	}

	//change state back to the previous state
	void RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	//accessors
	State<entity_type>* CurrentState() const{return m_pCurrentState;}
	State<entity_type>* PreviousState() const{return m_pPreviousState;}

};