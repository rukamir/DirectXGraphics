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

public:
	//Obj3D						*myObj;
	WorldManager();
	~WorldManager();

	Entity* GetEntityById(int id);

private:
	int m_iNVID;								// next valid ID

public:
	int GetNVID();								// get next valid ID
	void Update(float dt);
	void Render();

	void ResetWorldManager();

	static WorldManager* Instance();\
};

#endif	// end WORLDMANAGER_H