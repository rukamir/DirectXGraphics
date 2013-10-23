#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

class DirectInput
{
public:
	DirectInput(HINSTANCE insta, HWND hwnd, DWORD keyboardCoopFlags, DWORD mouseCoopFlags);
	~DirectInput();

	void poll();
	bool keyDown(char key);
	bool mouseButtonDown(int button);
	float mouseDX();
	float mouseDY();
	float mouseDZ();

	float mouseAX();
	float mouseAY();
	//HWND m_hwnd;

private:
	// Make private to prevent copying of members of this class.
	DirectInput(const DirectInput& rhs);
	DirectInput& operator=(const DirectInput& rhs);
		
private:
	IDirectInput8*       mDInput;

	IDirectInputDevice8* mKeyboard;
	char                 mKeyboardState[256]; 

	IDirectInputDevice8* mMouse;
	DIMOUSESTATE2        mMouseState;

	float m_mouseAXPos;
	float m_mouseAYPos;
};
extern DirectInput* gDInput;