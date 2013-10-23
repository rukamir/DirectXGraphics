#include "D3DApp.h"
#include <tchar.h>
#include <stdio.h>

D3DApp::D3DApp(void)
{
	m_pTextFPS = 0;
}

void D3DApp::CreateFPSDisplay()
{
	D3DXFONT_DESC fpsDesc;
	fpsDesc.Height          = 20;
    fpsDesc.Width           = 5;
    fpsDesc.Weight          = FW_BOLD;
    fpsDesc.MipLevels       = 0;
    fpsDesc.Italic          = false;
    fpsDesc.CharSet         = DEFAULT_CHARSET;
    fpsDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
    fpsDesc.Quality         = DEFAULT_QUALITY;
    fpsDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
	//fpsDesc.FaceName		=	L"Arial";
    strcpy_s(fpsDesc.FaceName, _T("Comic Sans MS"));

	D3DXCreateFontIndirect(this->m_pD3Device, &fpsDesc, &statFont);
}

D3DApp::~D3DApp(void)
{
	statFont->Release();
}

void D3DApp::Update(float dt)
{
	//update state machine
	calculateFPS(dt);
	DisplayStats();
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

void D3DApp::calculateFPS(float dt)
{
      // Make static so that their values persist across
      // function calls.
      static float numFrames   = 0.0f;
      static float timeElapsed = 0.0f;

      // Increment the frame count.
      numFrames += 1.0f;

      // Accumulate how much time has passed.
      timeElapsed += dt;

      if( timeElapsed >= 1.0f )
      {
            // Frames Per Second = numFrames / timeElapsed,
            // but timeElapsed approx. equals 1.0, so
            // frames per second = numFrames.

            mFPS = numFrames;

            // Average time, in milliseconds, it took to render a
            // single frame.
            mMilliSecPerFrame = 1000.0f / mFPS;

            // Reset time counter and frame count to prepare
            // for computing the average stats over the next second.
            timeElapsed = 0.0f;
            numFrames   = 0.0f;
      }
}

void D3DApp::DisplayStats()
{
	if (true)
	{
		// Make static so memory is not allocated every frame.
		static char buffer[256];


		sprintf_s(buffer, "FPS %.2f" , mFPS);
 
		RECT R = {50, 50, 0, 0};
		if (statFont)
			statFont->DrawText(0, buffer, -1, &R, DT_NOCLIP, D3DCOLOR_XRGB(255,255,255));
	}
}