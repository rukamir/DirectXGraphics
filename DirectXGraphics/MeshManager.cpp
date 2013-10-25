#include "MeshManager.h"

MeshManager::MeshManager(){
}

MeshManager::~MeshManager(){
	// Remove all mesh stuff
	for (const auto &meshComp : m_vMeshList){
		meshComp->bufMeshMaterial->Release();
		delete meshComp->material;
		meshComp->mesh->Release();
		delete meshComp->texture;
		delete meshComp;
	}
}

void MeshManager::Initialize(LPDIRECT3DDEVICE9 device){
	m_Device = device;
}

bool MeshManager::AddMeshToCollection(string fileName, string meshName){
	// Create new MeshComponents object
	MeshCompenents* meshStuff = new MeshCompenents();

	D3DXLoadMeshFromX(fileName.c_str(),				// load this file
					  D3DXMESH_SYSTEMMEM,			// load the mesh into system memory
					  m_Device,						// the Direct3D Device
					  NULL,							// we aren't using adjacency
					  &meshStuff->bufMeshMaterial,  // put the materials here
					  NULL,							// we aren't using effect instances
					  &meshStuff->numMaterials,		// the number of materials in this model
					  &meshStuff->mesh);			// put the mesh here

	// Check if mesh was successfully created
	if(meshStuff->mesh){
		// Add mesh to vector
		m_vMeshList.push_back(meshStuff);
		// Add mesh to map with name
		m_mMeshCollection.insert( make_pair(meshName, meshStuff) );
		return true;
	} else {
		// If wasnt successful delete allocated memory
		// return false
		delete meshStuff;
		return false;
	}
}

MeshCompenents*	MeshManager::GetMesh(string meshName){
	MeshCompenents* meshComp = NULL;

	meshComp = m_mMeshCollection.find(meshName)->second;

	return meshComp;
}