#ifndef MAPNPCMANAGER_H
#define MAPNPCMANAGER_H

#include <editor/NpcManager.h>
#include <model/MainModel.h>

namespace FigaroEditor
{
	class MapScene;

	class MapNPCManager
	{
	public:
		MapNPCManager(NpcManager* _npcManager);
		
		void addNPCFromBinary(NPC* binaryNPC);
		void addNewNPC();
		//persistence
		void loadMapNPCs();
	private:
		NpcManager* npcManager;
	};
}

#endif // MAPNPCMANAGER_H
