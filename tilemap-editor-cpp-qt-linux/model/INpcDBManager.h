#ifndef INPCWRITER_H
#define INPCWRITER_H

#include <editor/MapNpc.h>
#include <model/binaryModel/Map.h>
#include <model/binaryModel/NPC.h>
#include <list>

namespace FigaroEditor
{
    //Interface for managing NPCS in an abstract database
	class INpcDBManager
	{
	public:
		virtual ~INpcDBManager() {}
		virtual void writeNPCList(std::list<MapNpc*>* npcList) = 0;	
		virtual void readMapNPCs(std::list<NPC>* binaryNPCList) = 0;
		virtual void deleteNPC(int id) = 0;
    	};
}
#endif // INPCWRITER_H
