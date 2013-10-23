// GSP381 D3D Framework.cpp : Defines the entry point for the application.
//

//basic header files for windows
#include "D3DApp.h"
#include "Timer.h"
#include "DirectInput.h"
#include <Windows.h>

// define the screen resolution
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

//Visual Leak Detector
#include <vld.h>

//PROTOTYPES
// the WindowsProc function prototype
LRESULT CALLBACK WindowProc(	HWND hWnd,
								UINT message,
								WPARAM wParam,
								LPARAM lParam);

//entry point for any windows program
int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	//start timer
	TIM->Start();
	D3DApp dapp;
	//gTextureMan = new TextureManager();

	//the handle for the window, filled by a function
	HWND hWnd;
	//this struct holds info for the window  class
	WNDCLASSEX wc;



	//clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX) );

	//fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";

	//register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
    hWnd = CreateWindowEx(NULL,
                          "WindowClass1",    // name of the window class
                          "Influence Mapping by Jimmy Roland",   // title of the window
                          WS_OVERLAPPEDWINDOW,    // window style
                          300,    // x-position of the window
                          300,    // y-position of the window
                          SCREEN_WIDTH,    // width of the window
                          SCREEN_HEIGHT,    // height of the window
                          NULL,    // we have no parent window, NULL
                          NULL,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          NULL);    // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, nCmdShow);

	//start Visual Leak Detector
	VLDEnable();

	//create global for DirectInput pointer
	gDInput = new DirectInput(hInstance, hWnd, 
		DISCL_NONEXCLUSIVE |
		DISCL_FOREGROUND,
		DISCL_NONEXCLUSIVE |
		DISCL_FOREGROUND);


	//set up and initialize Direct3D
	dapp.InitD3D(hWnd,hInstance, true);
	// enter the main loop:
	//gD3DDev = *dapp.GetDevice();
    // this struct holds Windows event messages
    MSG msg;


    // Enter the infinite message loop
    while(TRUE)
    {
        // Check to see if any messages are waiting in the queue
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // translate keystroke messages into the right format
            TranslateMessage(&msg);

            // send the message to the WindowProc function
            DispatchMessage(&msg);
        }

        // If the message is WM_QUIT, exit the while loop
        if(msg.message == WM_QUIT)
            break;

		//DirectInput polling
		gDInput->poll();
		//dapp.SetMousePos(hWnd);

        // Run game code here
		dapp.Update( (float)TIM->GetTimeElapsed() );
    }

	VLDReportLeaks();
	//clean up DirectX and COM
	dapp.CleanDirect3D();

	//delete global
	delete gDInput;

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_DESTROY:
            {
                // close the application entirely
                PostQuitMessage(0);
                return 0;
            } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}