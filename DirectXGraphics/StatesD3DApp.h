#pragma once

#include "State.h"

class D3DApp;

class IntState
	: public State<D3DApp>
{
protected:
public:
	IntState();
	~IntState();

	void InitializeState(D3DApp*);
	void UpdateScene(D3DApp*, float dt);
	void RenderScene(D3DApp*);
	void OnResetDevice(D3DApp*);
	void OnLostDevice(D3DApp*);
	void LeaveState(D3DApp*);
};

class Demo1
	: public State<D3DApp>
{
protected:
public:
	Demo1();
	~Demo1();

	void InitializeState(D3DApp*);
	void UpdateScene(D3DApp*, float dt);
	void RenderScene(D3DApp*);
	void OnResetDevice(D3DApp*);
	void OnLostDevice(D3DApp*);
	void LeaveState(D3DApp*);
};

class Demo2
	: public State<D3DApp>
{
protected:
public:
	Demo2();
	~Demo2();

	void InitializeState(D3DApp*);
	void UpdateScene(D3DApp*, float dt);
	void RenderScene(D3DApp*);
	void OnResetDevice(D3DApp*);
	void OnLostDevice(D3DApp*);
	void LeaveState(D3DApp*);
};

