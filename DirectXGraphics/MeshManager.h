#pragma once

#include <D3DX9Mesh.h>
#include <map>
#include <vector>
#include <string>

#include "BaseComponent.h"

using namespace std;

class MeshManager{
private:
	LPDIRECT3DDEVICE9					m_Device;
	map<string, MeshComponents*>		m_mMeshCollection;
	vector<MeshComponents*>				m_vMeshList;
public:
	MeshManager();
	~MeshManager();
	void Initialize(LPDIRECT3DDEVICE9 device);

	bool AddMeshToCollection(string fileName, string meshName);
	MeshComponents*	GetMesh(string meshName);

private:
	void CreateSphereMesh();
};