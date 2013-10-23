#pragma once

#include "DirectX.h"

class D3DApp :
	public DirectX
{
protected:
	D3DXVECTOR2 m_MousePos;

public:
	void Update(float dt);

	D3DApp(void);
	~D3DApp(void);

	void InitD3D(HWND hWnd, HINSTANCE& hInst, bool bWindowed);

	D3DXVECTOR2 SetMousePos(HWND hwnd);
	D3DXVECTOR2 GetMousePos()
		{return m_MousePos;}

	LPDIRECT3DDEVICE9* GetDevice()
		{return &gD3DDev;}
	HWND* GetWindow()
		{return &m_hWnd;}
};