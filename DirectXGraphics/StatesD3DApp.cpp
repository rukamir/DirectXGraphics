#include "StatesD3DApp.h"
#include "D3DApp.h"
#include "DirectInput.h"
//#include "Camera.h"
#include "WorldManager.h"

IntState::IntState()
{
}

IntState::~IntState()
{
}

void IntState::InitializeState(D3DApp* app)
{
	//WMI->CreateSphere();
}
void IntState::UpdateScene(D3DApp* app, float dt)
{
	static bool test = false;
	if (!test){
		test = true;
		WMI->CreateSphere();
	}

	//CAM->Update();
	WMI->Update(dt);
}
void IntState::RenderScene(D3DApp* app)
{
}

void IntState::OnResetDevice(D3DApp* app)
{
}

void IntState::OnLostDevice(D3DApp* app)
{
}

void IntState::LeaveState(D3DApp* app)
{
}

//********************************************************
//3DObject Demo State
//********************************************************
Demo1::Demo1()
{
}

Demo1::~Demo1()
{
}

void Demo1::InitializeState(D3DApp* app)
{
}
void Demo1::UpdateScene(D3DApp* app, float dt)
{
}
void Demo1::RenderScene(D3DApp* app)
{
}

void Demo1::OnResetDevice(D3DApp* app)
{
}

void Demo1::OnLostDevice(D3DApp* app)
{
}

void Demo1::LeaveState(D3DApp* app)
{
}
