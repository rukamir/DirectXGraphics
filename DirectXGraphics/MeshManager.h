#pragma once

#include <D3DX9Mesh.h>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct MeshCompenents{
	DWORD					numMaterials;
	LPD3DXBUFFER			bufMeshMaterial;
	D3DMATERIAL9			*material;    // a pointer to a material buffer
	LPDIRECT3DTEXTURE9		*texture;    // a pointer to a texture
	LPD3DXMESH				mesh;
};

class MeshManager{
private:
	LPDIRECT3DDEVICE9					m_Device;
	map<string, MeshCompenents*>		m_mMeshCollection;
	vector<MeshCompenents*>				m_vMeshList;
public:
	MeshManager();
	~MeshManager();
	void Initialize(LPDIRECT3DDEVICE9 device);

	bool AddMeshToCollection(string fileName, string meshName);
	MeshCompenents*	GetMesh(string meshName);
};