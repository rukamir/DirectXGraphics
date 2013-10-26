#include "MeshManager.h"

MeshManager::MeshManager(){
}

MeshManager::~MeshManager(){
	// Remove all mesh stuff
	for (const auto &meshComp : m_vMeshList){
		if (meshComp->bufMeshMaterial)
			meshComp->bufMeshMaterial->Release();
		if (meshComp->material)
			delete meshComp->material;
		if (meshComp->mesh)
			meshComp->mesh->Release();
		if (meshComp->texture)
			delete meshComp->texture;
		delete meshComp;
	}
}

void MeshManager::Initialize(LPDIRECT3DDEVICE9 device){
	m_Device = device;

	// Create Basic meshes
	CreateSphereMesh();
}

bool MeshManager::AddMeshToCollection(string fileName, string meshName){
	// Create new MeshComponents object
	MeshComponents* meshStuff = new MeshComponents();

	D3DXLoadMeshFromX(fileName.c_str(),				// load this file
					  D3DXMESH_SYSTEMMEM,			// load the mesh into system memory
					  m_Device,						// the Direct3D Device
					  NULL,							// we aren't using adjacency
					  &meshStuff->bufMeshMaterial,  // put the materials here
					  NULL,							// we aren't using effect instances
					  &meshStuff->numMaterials,		// the number of materials in this model
					  &meshStuff->mesh);			// put the mesh here

	// retrieve the pointer to the buffer containing the material information
	D3DXMATERIAL* tempMaterials = (D3DXMATERIAL*)meshStuff->bufMeshMaterial->GetBufferPointer();

	// create a new material buffer for each material in the mesh
	meshStuff->material = new D3DMATERIAL9[meshStuff->numMaterials];
	meshStuff->texture = new LPDIRECT3DTEXTURE9[meshStuff->numMaterials];
	for(DWORD i = 0; i < meshStuff->numMaterials; i++)    // for each material...
	{
		meshStuff->material[i] = tempMaterials[i].MatD3D;    // get the material info...
		meshStuff->material[i].Ambient = meshStuff->material[i].Diffuse;    // and make ambient the same as diffuse
		meshStuff->texture[i] = 0;
		if (tempMaterials[i].pTextureFilename)
		{
			D3DXCreateTextureFromFile(m_Device, tempMaterials[i].pTextureFilename, &meshStuff->texture[i]);
		}

	}
	meshStuff->bufMeshMaterial->Release();

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

MeshComponents*	MeshManager::GetMesh(string meshName){
	MeshComponents* meshComp = NULL;

	meshComp = m_mMeshCollection.find(meshName)->second;

	return meshComp;
}

void MeshManager::CreateSphereMesh(){
	// Create MeshComponents for Sphere mesh
	MeshComponents* meshComp = new MeshComponents();
	meshComp->numMaterials		= 1;
	meshComp->bufMeshMaterial	= NULL;
	meshComp->material			= NULL;
	meshComp->texture			= NULL;

	//Create main sphere to be used to draw spheres place by user
	//Create a temporary sphere first
	ID3DXMesh* tempSphere;
	D3DXCreateSphere(m_Device, 1.0f, 10, 16, &tempSphere, 0);
	//Clone temp sphere to the main sphere and give its vertices a color value
	tempSphere->CloneMeshFVF( D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_DIFFUSE, m_Device, &meshComp->mesh );
	//Release the temp sphere
	tempSphere->Release();

	// Add sphere to meshCollection/List
	m_mMeshCollection.insert( make_pair("sphere", meshComp) );
	m_vMeshList.push_back( meshComp );
}