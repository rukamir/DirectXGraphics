#pragma once
// base class for states

#include <Windows.h>

template <class entity_type>
class State
{
public:
	State(){}
	~State(){}

	virtual void InitializeState(entity_type*)			= 0;
	virtual void UpdateScene(entity_type*, float dt)	= 0;
	virtual void RenderScene(entity_type*)				= 0;
	virtual void OnResetDevice(entity_type*)			= 0;
	virtual void OnLostDevice(entity_type*)				= 0;
	virtual void LeaveState(entity_type*)				= 0;
};