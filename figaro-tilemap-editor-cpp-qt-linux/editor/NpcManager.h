#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include "MapNpc.h"
#include <list>
#include <model/MainModel.h>

namespace FigaroEditor
{
	class GuiController;
}
namespace FigaroEditor
{
	class NpcManager
	{
	public:
	    NpcManager();
	    
	    void addNPCToList(MapNpc* npc);
	    void setSelectedNPC(MapNpc *npc);
	    MapNpc* getCurrentNPC() { return currentNPC; }
	    
	    std::list<MapNpc*>* getNPCList() {return &npcList;}
	    
	    // persistence
	    void removeCurrentNPC();
	    
	private:
	    MapNpc* currentNPC;
	    std::list<MapNpc*> npcList;
	};
}

#endif // NPCMANAGER_H
