#pragma once

#include <vector>
#include <map>

#include "BaseComponent.h"

using namespace std;

enum SHADERS{
	BASIC		= 0,
	OTHER		= 1
};

class ShaderManager{
private:
	// Map containing flag for shaders and
	// entities registers to the shader
	map<DWORD, vector<GraphicsComponent*>*>		m_mRegistry;
	LPDIRECT3DDEVICE9				m_Device;

public:
	ShaderManager();
	~ShaderManager();

	void Initialize(LPDIRECT3DDEVICE9 device);

	bool Register(DWORD, GraphicsComponent *ent);

	void Render(D3DXMATRIX view, D3DXMATRIX proj);

private:
	ID3DXEffect*		mFX;
	D3DXHANDLE			mhWVP;
	D3DXHANDLE			mhTech;
	D3DXHANDLE			mhColor;
	void SetUpBasic();
};