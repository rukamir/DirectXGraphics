#include "WorldManager.h"
#include "d3dUtil.h"
#include "DirectX.h"
#include "Sphere.h"

WorldManager::WorldManager()
{
	m_iNVID = 0;

	m_GraphicsCore = new GraphicsCore();
	m_GraphicsCore->Initialize(gD3DDev);

	// Add meshes
	m_GraphicsCore->m_MeshManager.AddMeshToCollection("airplane 2.x", "tiger");
}

WorldManager::~WorldManager()
{
	// Delete Entities
	std::vector<Entity*>::iterator i = m_vEntities.begin();
	for(; i != m_vEntities.end(); i++)
	{
		delete (*i);
	}
	m_vEntities.clear();

	if (m_GraphicsCore)
		delete m_GraphicsCore;
}

Entity* WorldManager::GetEntityById(int id)
{
	std::vector<Entity*>::iterator i = m_vEntities.begin();
	for(; i != m_vEntities.end(); i++)
	{
		if((*i)->GetID() == (unsigned int)id)
			return (*i);
	}
	return 0;
}

Entity* WorldManager::CreateSphere(){
	Sphere* sphere = new Sphere( GetNVID() );

	sphere->SetPosition(D3DXVECTOR3(0.0f, 0.0f,0.0f));

	//sphere->m_Graphics = m_GraphicsCore->CreateSphereGraphicsComponent( sphere->m_Graphics );
	sphere->m_Graphics = m_GraphicsCore->CreateGraphicsByName("sphere");
	sphere->m_Graphics->AssignPosition(&sphere->m_pos);

	m_vEntities.push_back(sphere);

	return sphere;
}

int WorldManager::GetNVID()
{
	m_iNVID++;
	return m_iNVID-1;
}

float GetSqDistance(D3DXVECTOR3 p1, D3DXVECTOR3 p2)
{
	float distSq = /*abs*/( 
		(p2.x - p1.x) * (p2.x - p1.x) + 
		(p2.y - p1.y) * (p2.y - p1.y) + 
		(p2.z - p1.z) * (p2.z - p1.z) );
	return distSq;
}

void WorldManager::Update(float dt)
{
	m_GraphicsCore->Update(dt);
	m_GraphicsCore->Render();
}

void WorldManager::ResetWorldManager()
{
	std::vector<Entity*>::iterator i = m_vEntities.begin();
	for(; i != m_vEntities.end(); i++)
	{
		delete (*i);
	}
	m_vEntities.clear();
	m_iNVID = 0;
}

WorldManager* WorldManager::Instance()
{
	static WorldManager instance; 
	return &instance;
}