#include "MapNpcManager.h"
#include <Core.h>

#include <editor/EditorDefinitions.h>
#include <editor/MapNpc.h>
#include <editor/MapScene.h>

#include <model/binaryModel/NPC.h>

#include <list>

using namespace FigaroEditor;

MapNPCManager::MapNPCManager(NpcManager *_npcManager):
        npcManager(_npcManager)
{
	
}

void MapNPCManager::loadMapNPCs()
{
	std::list<NPC> binaryNPCList;
	
	Core::model.persistenceModel.npcManager->readMapNPCs(&binaryNPCList);
	if(binaryNPCList.size() > 0u)
	{
		foreach (NPC currentNPC, binaryNPCList) 
		{
			addNPCFromBinary(&currentNPC);
		}
    	}
}

void MapNPCManager::addNPCFromBinary(NPC* binaryNPC)
{
	MapNpc* mapNPC = new MapNpc(npcManager);
	mapNPC->setPos(binaryNPC->x,binaryNPC->y);
	mapNPC->name = binaryNPC->name;
	mapNPC->id = binaryNPC->id;
	
	mapNPC->setZValue(vTopLayer);
	mapNPC->setPixmap(QPixmap(":/gui/npc.png"));
	npcManager->addNPCToList(mapNPC);	
	Core::mainWindow->mapScene.addItem(mapNPC);
}

void MapNPCManager::addNewNPC()
{
	MapNpc* mapNPC = new MapNpc(npcManager);
	mapNPC->setPos(0,0);
	mapNPC->setZValue(vTopLayer);
	
	mapNPC->setPixmap(QPixmap(":/gui/npc.png"));
	
	npcManager->addNPCToList(mapNPC);	
	Core::mainWindow->mapScene.addItem(mapNPC);
}
