#include "NpcManager.h"
#include <Core.h>
#include <editor/GuiController.h>

#include <algorithm>

using namespace FigaroEditor;

NpcManager::NpcManager() :
        currentNPC(NULL)
{
}


void NpcManager::addNPCToList(MapNpc *npc)
{
	npcList.push_back(npc);
}

void NpcManager::setSelectedNPC(MapNpc* npc)
{
	currentNPC = npc;
    	Core::guiController.activateNPCTab();
}

void NpcManager::removeCurrentNPC()
{
	unsigned int previousListSize = npcList.size();
	
	npcList.remove(currentNPC);
	Q_ASSERT(npcList.size() == previousListSize -1);
	Core::model.persistenceModel.npcManager->deleteNPC(currentNPC->id);
	
	delete currentNPC;
	currentNPC = NULL;	
}
