#include "WorldManager.h"
#include "d3dUtil.h"
#include "DirectX.h"

WorldManager::WorldManager()
{
	m_iNVID = 0;

	m_GraphicsCore = new GraphicsCore();
	m_GraphicsCore->Initialize(gD3DDev);
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

void WorldManager::Render()
{	
	//// Clear the backbuffer and depth buffer.
	//HR(gD3DDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0));

	//HR(gD3DDev->BeginScene());


	//FXM->SetTechnique();
	//GraphicsM->Render(FXM->GetFX(), FXM->GetWVP(), CAM->GetViewMatrix(), CAM->GetProjectionMatrix());
	//	 myObj->Render(D3DXVECTOR3(0.0f, 0.0f ,0.0f));


	//HR(gD3DDev->EndScene());

	//// Present the backbuffer.
	//HR(gD3DDev->Present(0, 0, 0, 0));
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