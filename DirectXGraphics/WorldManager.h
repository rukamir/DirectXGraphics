#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <vector>
#include "GraphicsCore.h"
#include "Entity.h"
//#include "3DObj.h"

#define WMI WorldManager::Instance()

class WorldManager
{
private:
	GraphicsCore*				m_GraphicsCore;
	std::vector<Entity*>		m_vEntities;
	int m_iNVID;								// next valid ID

public:
	WorldManager();
	~WorldManager();

	Entity* GetEntityById(int id);

	// Create Functions
	Entity* CreateSphere();

private:

public:
	int GetNVID();								// get next valid ID
	void Update(float dt);

	void ResetWorldManager();

	static WorldManager* Instance();
};

#endif	// end WORLDMANAGER_H