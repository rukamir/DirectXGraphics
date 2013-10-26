#pragma once

#include <d3dx9.h>
#include <vector>
#include <map>
#include <string>

#include "Camera.h"
#include "ShaderManager.h"
#include "MeshManager.h"

class GraphicsCore {
private:
	LPDIRECT3DDEVICE9		m_Device;
	Camera					*m_camera;
	ShaderManager			m_ShaderManager;

public:
	MeshManager				m_MeshManager;
	GraphicsCore();
	~GraphicsCore();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Shutdown();

	void OnResetDevice();
	void OnLostDevice();

	void Update(float dt);
	void Render();

	GraphicsComponent* CreateSphereGraphicsComponent();
	GraphicsComponent* CreateGraphicsByName(string graphicName);

private:
	void loadMesh(std::string meshName, std::string meshFile);

	// Stats display
	ID3DXFont*	statFont;
	float mFPS;
	float mMilliSecPerFrame;
	void calculateFPS(float dt);
	void DisplayStats();
};