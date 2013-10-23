#ifndef DIRECTX_H
#define DIRECTX_H

#include <d3d9.h>
#include <d3dx9.h>

// Direct3D libraries
#pragma comment (lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define SAFE_RELEASE(x) if(x){x->Release(); x = 0;}

class DirectX
{
protected:
	HWND m_hWnd;
	bool m_bVsync;

	// Direct3D vars
	LPDIRECT3D9				m_pD3DObject;
	LPDIRECT3DDEVICE9		m_pD3Device;
	D3DCAPS9				m_D3DCaps;
	D3DPRESENT_PARAMETERS	md3dPP;

public:
	DirectX();
	virtual ~DirectX();

	void InitializeDirect3D(HWND hWnd, HINSTANCE& hInst, bool bWindowed);
	void EnableFullScreenMode(bool enable);
	void BeginScene();
	void EndScene();

	bool IsDeviceLost();
	void OnLostDevice();
	void OnResetDevice();

	void CleanDirect3D();

	LPDIRECT3DDEVICE9 GetDevice()
		{return m_pD3Device;}
};

extern LPDIRECT3DDEVICE9 gD3DDev;
#endif