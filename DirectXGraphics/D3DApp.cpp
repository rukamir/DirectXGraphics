#include "D3DApp.h"
#include <tchar.h>

D3DApp::D3DApp(void)
{
}

D3DApp::~D3DApp(void)
{
}

void D3DApp::Update(float dt)
{
}

void D3DApp::InitD3D(HWND hWnd, HINSTANCE& hInst, bool bWindowed)
{
	this->InitializeDirect3D(hWnd, hInst, bWindowed);
}

D3DXVECTOR2 D3DApp::SetMousePos(HWND hwnd)
{
	// Get position of mouse on the screen
	static int number = 0;
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(hwnd, &mouse);
 
	m_MousePos.x = (float)mouse.x;
	m_MousePos.y = (float)mouse.y;

	return m_MousePos;
}
