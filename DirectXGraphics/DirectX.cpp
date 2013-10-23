#include "DirectX.h"
#include "d3dUtil.h"

LPDIRECT3DDEVICE9 gD3DDev = 0;

DirectX::DirectX()
{
	m_bVsync		= true;
	m_pD3DObject	= 0;
	m_pD3Device	= 0;
}

DirectX::~DirectX()
{
	ReleaseCOM(m_pD3DObject);
	ReleaseCOM(m_pD3Device);
}

void DirectX::InitializeDirect3D(HWND hWnd, HINSTANCE& hInst, bool bWindowed)
{
	// Presentation Parameters
	ZeroMemory(&md3dPP, sizeof(md3dPP));
	md3dPP.BackBufferWidth            = 0; 
	md3dPP.BackBufferHeight           = 0;
	md3dPP.BackBufferFormat           = D3DFMT_UNKNOWN;
	md3dPP.BackBufferCount            = 1;
	md3dPP.MultiSampleType            = D3DMULTISAMPLE_NONE;
	md3dPP.MultiSampleQuality         = 0;
	md3dPP.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	md3dPP.hDeviceWindow              = m_hWnd;
	md3dPP.Windowed                   = true;
	md3dPP.EnableAutoDepthStencil     = true; 
	md3dPP.AutoDepthStencilFormat     = D3DFMT_D24S8;
	md3dPP.Flags                      = 0;
	md3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	md3dPP.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	m_hWnd = hWnd;
	m_pD3DObject = Direct3DCreate9(D3D_SDK_VERSION);

	// Get window size
	RECT rect;
	GetWindowRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

    D3DPRESENT_PARAMETERS D3Dpp;    // create a struct to hold various device information
	ZeroMemory(&D3Dpp, sizeof(D3Dpp));    // clear out the struct for use
    
	D3Dpp.hDeviceWindow					= hWnd;										// Handle to the focus window
	D3Dpp.Windowed						= bWindowed;								// Windowed or Full-screen boolean
	D3Dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;								// Format of depth/stencil buffer, 24 bit depth, 8 bit stencil
	D3Dpp.EnableAutoDepthStencil		= TRUE;										// Enables Z-Buffer (Depth Buffer)
	D3Dpp.BackBufferCount				= 1;										// Change if need of > 1 is required at a later date
	D3Dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;							// Back-buffer format, 8 bits for each pixel
	D3Dpp.BackBufferHeight				= height;									// Make sure resolution is supported, use adapter modes
	D3Dpp.BackBufferWidth				= width;									// (Same as above)
	D3Dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;					// Discard back-buffer, must stay discard to support multi-sample
	D3Dpp.PresentationInterval			= m_bVsync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE; // Present back-buffer immediately, unless V-Sync is on								
	D3Dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;		// This flag should improve performance, if not set to NULL.
	D3Dpp.FullScreen_RefreshRateInHz	= bWindowed ? 0 : D3DPRESENT_RATE_DEFAULT;	// Full-screen refresh rate, use adapter modes or default
	D3Dpp.MultiSampleQuality			= 0;										// MSAA currently off, check documentation for support.
	D3Dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;						// MSAA currently off, check documentation for support.

    // Check device capabilities
	DWORD deviceBehaviorFlags = 0;
	m_pD3DObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);

	// Determine vertex processing mode
	if(m_D3DCaps.DevCaps & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		// Hardware vertex processing supported? (Video Card)
		deviceBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;	
	}
	else
	{
		// If not, use software (CPU)
		deviceBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; 
	}
	
	// If hardware vertex processing is on, check pure device support
	if(m_D3DCaps.DevCaps & D3DDEVCAPS_PUREDEVICE && deviceBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		deviceBehaviorFlags |= D3DCREATE_PUREDEVICE;	
	}
	
	// Create the D3D Device with the present parameters and device flags above
	m_pD3DObject->CreateDevice(
		D3DADAPTER_DEFAULT,		// which adapter to use, set to primary
		D3DDEVTYPE_HAL,			// device type to use, set to hardware rasterization
		hWnd,					// handle to the focus window
		deviceBehaviorFlags,	// behavior flags
		&D3Dpp,					// presentation parameters
		&m_pD3Device);			// returned device pointer

	//set global
	gD3DDev = m_pD3Device;
}

void DirectX::EnableFullScreenMode(bool enable)
{
	// Switch to fullscreen mode.
	if( enable )
	{
		// Are we already in fullscreen mode?
		if( !md3dPP.Windowed ) 
			return;

		int width  = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);

		md3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
		md3dPP.BackBufferWidth  = width;
		md3dPP.BackBufferHeight = height;
		md3dPP.Windowed         = false;

		// Change the window style to a more fullscreen friendly style.
		SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_POPUP);

		// If we call SetWindowLongPtr, MSDN states that we need to call
		// SetWindowPos for the change to take effect.  In addition, we 
		// need to call this function anyway to update the window dimensions.
		SetWindowPos(m_hWnd, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);	
	}
	// Switch to windowed mode.
	else
	{
		// Are we already in windowed mode?
		if( md3dPP.Windowed ) 
			return;

		RECT R = {0, 0, 800, 600};
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		md3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
		md3dPP.BackBufferWidth  = 800;
		md3dPP.BackBufferHeight = 600;
		md3dPP.Windowed         = true;
	
		// Change the window style to a more windowed friendly style.
		SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);

		// If we call SetWindowLongPtr, MSDN states that we need to call
		// SetWindowPos for the change to take effect.  In addition, we 
		// need to call this function anyway to update the window dimensions.
		SetWindowPos(m_hWnd, HWND_TOP, 100, 100, R.right, R.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
	}

	// Reset the device with the changes.
	OnLostDevice();
	HR(gD3DDev->Reset(&md3dPP));
	OnResetDevice();
}


void DirectX::BeginScene()
{
	// clear the window to a deep blue
    m_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

	m_pD3Device->BeginScene();    // begins the 3D scene
}

void DirectX::EndScene()
{
    m_pD3Device->EndScene();    // ends the 3D scene

    m_pD3Device->Present(NULL, NULL, NULL, NULL);    // displays the created frame
}


bool DirectX::IsDeviceLost()
{
	HRESULT hr = gD3DDev->TestCooperativeLevel();
	
	if( hr == D3DERR_DEVICELOST )
	{
		Sleep(20);
		return true;
	}
	else if( hr == D3DERR_DRIVERINTERNALERROR )
	{
		MessageBox(0, "Internal Driver Error", 0, 0);
		PostQuitMessage(0);
		return true;
	}
	else if( hr == D3DERR_DEVICENOTRESET )
	{
		OnLostDevice();
		HR(gD3DDev->Reset(&md3dPP));
		OnResetDevice();
		// Not lost anymore
		return false;
	}
	else
	{
		// Not lost anymore
		return false;
	}
}

void DirectX::OnLostDevice()
{
}

void DirectX::OnResetDevice()
{
}

void DirectX::CleanDirect3D()
{
	m_pD3Device->Release();
	m_pD3DObject->Release();
}