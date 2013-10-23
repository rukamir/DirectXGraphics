#pragma once

#include <d3dx9.h>
#include <vector>
#include <map>
#include <string.h>

#include "Camera.h"
#include "ShaderManager.h"

//class Camera;

class GraphicsCore {
private:
	LPDIRECT3DDEVICE9		m_Device;
	//GfxStats				*gStats;
	Camera					*m_camera;
	ShaderManager			m_ShaderManager;

	//std::map<std::string, MeshComponents*>	m_mMeshes;
	//std::vector<MeshComponents>				*allMesh;

public:
	GraphicsCore();
	~GraphicsCore();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Shutdown();

	void OnResetDevice();
	void OnLostDevice();

	void Update(float dt);
	void Render();

private:
	//Effect Handles
	ID3DXEffect *m_FX;

	void loadMesh(std::string meshName, std::string meshFile);
};