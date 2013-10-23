#pragma once

#include "DirectX.h"

class D3DApp :
	public DirectX
{
protected:
	ID3DXFont*	m_pTextFPS;
	D3DXVECTOR2 m_MousePos;
	D3DVERTEXELEMENT9 myVert;
	

public:
	void Update(float dt);

	D3DApp(void);
	~D3DApp(void);

	void InitD3D(HWND hWnd, HINSTANCE& hInst, bool bWindowed);

	D3DXVECTOR2 SetMousePos(HWND hwnd);
	void ChangeState(int);
	void ChangePreviousState();

	D3DXVECTOR2 GetMousePos()
		{return m_MousePos;}

	LPDIRECT3DDEVICE9* GetDevice()
		{return &gD3DDev;}
	HWND* GetWindow()
		{return &m_hWnd;}
	void CreateFPSDisplay();

	D3DVERTEXELEMENT9 GetMyVert(){return myVert;}

private:
	ID3DXFont*	statFont;
	float mFPS;
	float mMilliSecPerFrame;

	void calculateFPS(float dt);
	void DisplayStats();
};